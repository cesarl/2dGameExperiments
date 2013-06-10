---
layout: post
title: "Tetris - Première version | V1"
description: "Retour d'expérience sur la première version du Tetris"
category: Tetris
tags: [V1, Tetris, Allegro5, c++, singleton pattern, component based architecture, scenes]
---
{% include JB/setup %}

On ne peut pas pour le moment parler de première version du Tetris car ce dernier n'est pas encore complètement terminé, reste :
- Musique et sons
- Enregistrement des scores (actuellement buggy)
- Affichage des scores
- Design - basique :)

Cependant beaucoup de choses y ont été implémentées, et je préfère arrêter ma V1 ici avant d'aller plus loin.

Je vais tenter de survoler les principaux développements et problèmes rencontrés. Cependant le code est simple et parle de lui même. C'est pourquoi je ne m'étale pas en explications techniques.

### Bibliographie :

#### Singleton pattern :
- [Wikipedia](http://en.wikipedia.org/wiki/Singleton_pattern)
- _Advanced 2D game development_, de Jonathan S. Harbour

#### Component based architecture
- [Evolve your hierarchy](http://cowboyprogramming.com/2007/01/05/evolve-your-heirachy/)
- [Stack overflow](http://stackoverflow.com/questions/1901251/component-based-game-engine-design)
- Avant tout Google est votre ami
- J'explique plus bas que l'implementation que j'en ai faite dans cette première version est entièrement mauvaise.

### Les assets managers

J'ai créé plusieurs types d'assets managers :
- Pour les images (ImageManager)
- pour les polices (FontManager)
- pour les sauvegardes (SaveManager) // pas entièrement fonctionnel

Il est prévu d'en créer un pour gérer les sons.

Ces managers ont pour fonction de charger les assets désirés et de les renvoyer lorsque cela leur est demandé.

Ils stockent ces derniers dans une std::map avec pour clef le path - ``path-fontsize`` pour le FontManager.

Ils utilisent tous le [singleton pattern](http://en.wikipedia.org/wiki/Singleton_pattern).

> _Points faibles et critiques_
> - pas de chargement asynchrone (ne permet pas d'implémenter une barre de chargement par exemple)
> - pourraient être réunis dans un seul AssetManager

### L'architecture générale

Le code _a priori_ parle de lui même.

L'architecture a été (mal) pensée sur une base "horizontale", CAD :

**Un event manager**

- qui se charge de collecter les différents events :
  - Inputs
  - Timer
- auquel va être lié une instance de SceneManager

**Scene manager**

- se charge de la gestion de différentes scènes (menu, sous menu, jeux)
- décide de quelle scène afficher / mettre à jour
- en fonction de l'état des scènes (visibles, actives) il leur passera ou non les events (inputs, refresh timer...)

**Les scènes**

- sont toutes des classes héritières de l'abstract class AScene
- se chargent de la gestion des Entités / des inputs / de l'affichage

**Les entités**

- les ``Entity`` ne sont pas des abstract class - explication plus bas
- Elles contiennent
  - coordonnées et dimensions
  - une liste de composantes
- A l'update elles appellent la méthode ``update`` de chacune de leur composante
- Idem pour le ``draw``
- Les différentes composantes sont : images, sprite et texte

#### Explication des choix


> **Q: Qu'est ce que ce système d'entité et de composante ?**

**A: J'ai préféré essayer d'implémenter un système basé sur les composants par souci d'évolutivité**

En effet, j'aurais pu, beaucoup plus simplement faire de l'héritage classique du type :
+ Entity
 + EntityText
 + EntityImage
  + EntitySprite

Cependant, si je veux pouvoir à terme, ajouter des particules, des explosions, des rotations, des zooms, je devrais procéder de la sorte:
+ Entity
 + EntityText
  + EntityTextScalable
  + EntityTextRotable
   + EntityTextExplosion
+...
Ça n'aurais pas été maintenable - j'ai déjà trop souvent fait cette erreur

C'est pourquoi j'ai essayé d'implémenter pour la première fois dans ma vie palpitante de petit développeur, une architecture de type component based ! Et pour le moment on peut toujours parler d'erreur car nous sommes loin de la solution flexible et évolutive ! Pas grave, on est la pour ça ^^

> **Q: Pourquoi dis tu que ton implementation du component based design est foireuse ?**

**A: Il n'y a qu'à regarder le code du ``TetrisGrid.cpp`` hehe - c'est là où se passe la quasi totalité du jeu.**

Dans la fonction ``p_newShape()``,  on voit que je créé une nouvelle forme à faire tomber dans le Tetris.

Pour ça je commence par aller chercher les Entités déjà créées et inutilisées. Jusque là pas de problèmes. Tant que l'on modifie l'Entity tout se passe bien (width, height, position, visibility ...). Cependant, dès que l'on veut communiquer avec ses composantes ça se complique.

Je rappelle l'architecture de mon component based design (CBD) :

Les composantes sont des classes héritières de l'abstract class ``AContentComponent``.
Les ``Entity`` contiennent une ``std::list<AContentComponent*>`` (content_) de composantes. Classées selon un ordre de priorité (voir méthode ``setContentComponent()``).

Chaque composante implémente une méthode ``update`` et ``draw`` - pures dans ``AContentComponent``.

D'autre méthodes spécifiques peuvent être ajoutées à chaque composante, par exemple la composante Texte aura la méthode ``getText()`` qui servira à en récupérer la valeur sous la forme d'un string.

Mais imaginons que l'on veuille ajouter une composante de type texte à l'entity ``myEntity`` :

{% highlight c++ %}
int                                 main()
{
  ContentComponentText              *myComponent;
  Entity                            *myEntity;

  myComponent = new ContentComponentText("assets/fonts/LilitaOne-Regular.ttf", 80);
  *myComponent = "My component based architecture ";

  myEntity = new Entity();
  myEntity->setPos(200, 200);
  myEntity->setContentComponent(myComponent);
  tellMeTheTruth(myEntity);
  return (0);
}
{% endhighlight %}

Si l'on veut que la fonction ``tellMeTheTruth()`` concat le string contenu dans la composante avec un nouveau string, comment allons nous faire ?

{% highlight c++ %}
void					tellMeTheTruth(Entity *entity)
{
  AContentComponent			*abstractComponent;
  ContentComponentText			*textComponent;

  abstractComponent = entity->getContentComponent(TEXT_TYPE);
  if (!abstractComponent)
    {
      std::cerr << "Il y a un probleme mon capitaine, l'entite ne contient aucune composante de type Text" << std::endl;
	//a priori, si on fait un minimum attention ça ne peut pas arriver
    }
  textComponent = dynamic_cast<ContentComponentText*>(abstractComponent);
  textComponent += "sucks !!!!";
  entity->draw();
}
{% endhighlight %}

Ça en fait du texte pour afficher "My component based architecture sucks" !!!

De plus on va rencontrer d'autre problèmes, tel que la communication entre les différentes composantes.
En effet, comment les faire communiquer entre elles ?

On pourrait aussi relever plusieurs incohérences telles que :
- Pourquoi mettre les coordonnées et dimensions dans l'entité et ne pas plutôt en faire une composante ?
- Pourquoi la composante Sprite hérite elle de la composante Image ? Ne devrait elle pas plutôt la compléter au sein de l'entité ?
- ...

**Pour résumer**

Aujourd'hui la tentative d'implementation d'un CBD que j'ai faite ne permet pas :
- La communication entre les différentes composantes d'une même entité.
  - Message
  - Données
- La communication entre les différentes composantes d'entités séparées.
- D'appeler simplement certaines méthodes des composantes (exemple de ``getText()``).
- ...

__Cependant :__
- Le coeur y était ^^
- Je me suis mieux documenté depuis, et je travaille déjà sur une refonte

**Q: Tu n'as vraiment pas l'air très content de ton travail, mais rassure moi, au moins j'imagine que tu es satisfait de ton architecture globale ?**

Hahahahha ! Mais je suis toujours content - je te répète que je suis la pour apprendre de mes erreurs !

Je ne peux pas me dire satisfait de l'archi globale, cette horizontalité m'a bloqué à plusieurs reprises, et j'ai été obligé de trouver des solutions - pas si bêtes à mon sens mais pour le moment très mal implémentées.

Nous sommes d'accord que tout se passe dans les Scenes. Certaine vont proposer un menu, d'autre des phases de jeux. Par exemple ici nous avons une scène pour le menu principale, une pour le jeu en lui même, une autre qui s'affiche lorsque l'on met le tetris en pause, et enfin une dernière, au moment du game over et de l'enregistrement des scores.

Toutes ces scènes sont des classes à part entière, héritières de l'abstract class ``AScene``. Quand on en quitte une, une autre s'affiche. Mais alors il faut bien qu'elles communiquent entre elles !
Ce à quoi je n'avais pas pensé au départ ([je sais, je sais ...](http://25.media.tumblr.com/tumblr_lyl2qa5RQH1qcfbz9o1_250.gif)).

Pour remédier à ce problème, j'ai implémenté - un peu à l'arrache - un système de communication entre le différentes scènes.
Dans un premier temps elles pouvaient envoyer au sceneMamager des messages (``int flag, bool onOff, std::string sceneName``).
Ça fonctionnait bien ; quand des scènes se désactivaient elles demandaient poliment à d'autre de les remplacer.

Puis arriva le problème de la communication de données entre les différentes scènes ! Autre affaire !
En effet, par exemple, la scène de jeu, une fois terminée va s'éteindre pour être replacé par la scène de game over. Cependant c'est la scène de jeu qui calcul le score, et à priori, celle de game over n'a aucune idée du score que vous venez de réaliser. J'ai donc surchargé la fonction d'envoi de message en lui permettant de transporter des donnes (des void* :/).

Si vous trouvez toujours ce genre de communication intelligente, allez jeter un coup d'oeil au code de SceneGameOver.cpp, vous verrez...

Si vous n'êtes toujours pas convaincu, laissez moi vous expliquer pourquoi c'est mal :

- Les scènes sont appelées a l'aide de string ! Ça tient le coup pour passer de scène en scène une fois toutes les 2 minutes, mais imaginons deux scènes actives en même temps et échangeant beaucoup de donnée très fréquemment. Ça devient lourd ! Comme diraient les geeks "ze pas trez zopti tout za".
- Tu as un super moyen de transférer les infos du haut de l'échelle (EventManager) jusqu'en bas (Entity et ses composante) mais tu es obligé de trickser avec des ``enum`` et des void* pour remonter le cours du flux d'information !
- La on te parle de communication entre scène, imagine ce que ça serait d'essayer de faire communiquer des scènes avec l'event manager ?
- Et je n'ose pas mentionner l'utilisation de void* à la place de template etc etc...

Et puis il n'y a pas que ça qui pèche dans ce système.
Je vais tenter d'en faire une liste la plus complète possible :
- Chaque scène est une classe a part entière ! Pour ajouter un simple menu, il faut donc définir une nouvelle classe !
- ...

Bon cet article est un peu chaotique ^^, j'essaierais de faire mieux la prochaine fois !