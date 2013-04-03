---
layout: post
title: "Tetris - Premiere version | V1"
description: "Retour d'experience sur la premiere version du Tetris"
category: Tetris
tags: [V1, Tetris, Allegro5, c++]
---
{% include JB/setup %}

La premiere version du Tetris n'est pas encore complement terminee, reste :
- Musique et sons
- Enregistrement de score (actuellement buggy)
- Affichage des scores
- Design - basique :)

Beaucoup de choses y ont ete implementees, je vais tenter de ne pas en oublier

### Les assets managers

J'ai cree plusieurs type d'asset manager :
- Pour les images (ImageManager)
- pour les polices (FontManager)
- pour les sauvegardes (SaveManager) // pas entierement fonctionnel

Il est prevu d'en creer un pour gerer les sons.

Ces managers ont pour fonction de charger les assets desires et de les renvoyer lorsque cela leur est demande.

Ils stockent ces derniers dans une std::map avec pour clef le path - ``path-fontsize`` pour le FontManager.

Ils utilisent tous le [singleton pattern](http://en.wikipedia.org/wiki/Singleton_pattern).

> _Points faibles et critiques_
> - pas de chargement asynchrone (ne permet pas d'implementer une barre de chargement par exemple)
> - pourraient etre reunni dans un seul AssetManager

### L'architecture generale

Le code a priori parle de lui meme pour ce qui de l'achi generale.

L'architecture a ete (mal) pensee sur une base "horizontale", cad :

Un event manager

- qui se charge de collecter les differents events :
  - Inputs
  - Timer
- auquel va etre lie une instance de SceneManager

Scene manager

- se charge de la gestion de differentes scenes (menu, sous menu, jeux)
- decide de quel scene afficher / mettre a jour
- en fonction de l'etat de scenes (visibles, activent) il leur passera ou non les events (inputs, refresh timer...)

Les scenes

- toutes des classes heritieres de l'abstract class AScene
- se chargent de la gestion des Entites / des inputs / de l'affichage

Les entites

- les ``Entity`` ne sont pas des abstract class - explication plus bas
- Elles contiennent
  - un jeu de coordonnees et dimensions
  - une liste de composantes
- A l'update elles appellent la methode ``update`` de chacune de leur composante
- Idem pour le ``draw``
- Les differentes composantes sont : images, sprite et texte

#### Explication des choix


> **Q: Qu'est ce que ce systeme d'entity et de composante ?**


**A: J'ai prefere essayer d'implementer un syteme base sur les composants par souci d'evolutivite**

En effet, j'aurais pu, beacoup plus simplement faire de l'heritage classique du type :
+ Entity
 + EntityText
 + EntityImage
  + EntitySprite

Cepedant, si je rajoute a terme, des particlues, des explosions, des roations, des zoom, je devrais prodeder de la sorte:
+ Entity
 + EntityText
  + EntityTextScalable
  + EntityTextRotable
   + EntityTextExplosion
+...
Ca n'aurais pas ete maintenable - j'ai deja trop souvent fait cette erreur

C'est pourquoi j'ai essayer d'implementer pour la premiere fois dans ma vie palpitante de petit developpeur, une architecture de type component based ! Et pour le moment on peut toujours parler d'erreur car nous sommes loin de la solution flexible et evolutive ! Pas grave, on est la pour ca ^^

> **Q: Pourquoi dis tu que ton implementation du component based design est foireuse ?**

**A: Il n'y a qu'a regarder le code du TetriGrid.cpp hehe - c'est la ou se passe la quasi totalite du jeu.**
Dans la fonction p_newShape() on voit je cree une nouvelle forme a faire tomber dans le tetris.

Pour ca je commence par aller chercher les Entites deja cree et inutilises. Jusque la pas de probleme. Tant que l'oon modifie l'Entity tout se passe bien (width, height, position, visibility ...). Cependant, des que l'on veut communiquer avec se composantes ca se complique.

Je rappelle l'architecture de mon component based design (CBD) :
Les composantes sont des classes heritieres de l'abstract class ``AContentComponent``.n
Les ``Entity`` contiennent une ``std::list<AContentComponent*>`` (content_) de composantes. Classee en fonction de priorite (voir methode setContentComponent()).

Chaque composante implemente une methode update et draw - pures dans AContentComponent

D'autre methodes peuvent etre ajoute propres a chaque composante, par exemple la composante Texte aura la methode getText() pour en recuperer la valeur sous la forme d'un string.

Mais imaginons que l'on ai ajoute une composante de type texte a l'entity ``myEntity`` a laquelle on ajoute une composante texte :

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

Si l'on veut que la fonction ``tellMeTheTruth()`` ajoute a la composante texte un string, comment allons nous faire ?

{% highlight c++ %}
void					tellMeTheTruth(Entity *entity)
{
  AContentComponent			*abstractComponent;
  ContentComponentText			*textComponent;

  abstractComponent = entity->getContentComponent(TEXT_TYPE);
  if (!abstractComponent)
    {
      std::cerr << "Il y a un probleme mon capitaine, l'entite ne contient aucune composante de type Text" << std::endl;
	//a priori, si on fait un minimum attention ca ne peut pas arriver
    }
  textComponent = dynamic_cast<ContentComponentText*>(abstractComponent);
  textComponent += "sucks !!!!";
  entity->draw();
}
{% endhighlight %}

Ca en fait du texte pour afficher ""My component based architecture sucks" !!!

De plus on va rencontrer d'autre problemes, tel que la communication entre les differentes composantes.

Bref, j'imagine que ca repond asse bien a la question. Tout ca pour dire, l'implementation component based que j'ai pondu est clairement bancale ^^

**Q: Tu n'as vraiment pas l'air tres content de ton travail, mais rassure moi, au moins j'imagine que tu es satisfait de ton architecture globale ?**

Hahahahha ! Mais je suis toujours content - je te repete que je suis la pour apprendre de mes erreurs !

Je ne peux pas me dire satisfait de l'archi globale, cette horizontalite m'a blocke a plusieurs reprise, et j'ai ete oblige de trouver des solutions - pas si betes a mon sens mais pour le moment mal implementees.

Nous sommes d'accord que tout se passe dans les Scenes. Certaine vont proposer un menu, d'autre des phases de jeux. Par exemple ici nous avons une scene pour le menu principale, une pour le jeu en lui meme, une autre qui s'affiche lorsque l'on met le tetris en pause, et enfin une derniere au moment du game over et de l'enregistrment de scores. Toutes ces scenes sont des classes a part entiere, heritiere de l'abstract class ``AScene``. Quand on en quitte une, une autre s'affiche. Mais alors il faut bien qu'elle comuniquent entre elles ! Ce a quoi je n'avais pas pense au depart ([je sais, je sais ...](http://www.sinn-frei.com/media/2012/16469_017.gif)).

Pour remedier a ce probleme, j'ai implementer - un peu a l'arrache - un systeme de communication entre le differentes scenes. Dans un premier temps elles pouvaient envoyer au sceneMamager des messages (int flag, bool onOff, std::string sceneName). Ca fonctionnait bien ; quand des scenes se desactivaient elles demandaient poliement a d'autre de les remplacer.

Puis arriva le probleme de la communication de donnee entre les differentes scenes ! Autre affaire ! En effet, par exemple, la scene de jeu, une fois termine va s'eteindre pour etre replace par la scene de game over. Cependant c'est la scene de jeu qui calcul le score, et a priori, celle de game over n'a aucune idee du score que vous venez de realiser. J'ai donc surcharge la fonction d'envoi de message en lui permettant de transporter des donnes (des void* :/).

Si vous trouvez toujours ce genre de communication inteligente, allez jeter un coup d'oeil au code de SceneGameOver.cpp, vous verrez... Si vous n'etes toujours pas convaincu, laissez moi vous expliquer pourquoi c'est mal :
- Les scenes sont appelee a l'aide de string ! Ca tient le coup pour passer des scene en scene une fois toutes les 2 minutes, mais imaginons deux scenes actives en meme temps et echangeant beaucoup de donnee tres frequemment. Ca devient lourd ! Comme diraient les geeks "ze pas trez zopti tout za".
- Tu as un super moyen de transferer les infos du haut de l'echelle (EventManager) jusqu'en bas (Entity et ses composante) mais tu es oblige de trickser avec des enums et des void* pour remonter le cours du flux d'information, ca tesemble vraiment logique ??? !
- La on te parle de communication entre scene, imagine ce que ca serait d'essayer de faire communiquer des scenes avec l'event manager ?
- et je n'ose pas mentionner l'utilisation de void* a la place de template etc etc...

Et puis il n'y a pas que ca qui peche dans ce systeme.

Imaginons demain j'arrive a brancher un(e) super game designer - on peut toujours rever, j'ai deja du mal a brancher des etudiants en informatiques - qui touchote au code et qui a vraiment trop envie de mettre en place des scenes.

Je lui explique : "Alors la, si tu veux ajouter un menu bah tu cree une class SceneNomDuMenu qui herite de AScene. Ensuite si tu veux mettre du texte tu cree des variables membres de la classe, et tu leur ajoute un ou des composants de ton choix ................". Bref, vous avez compris, que chaque menu soit un heritage de classe, c'est pas tip top - sauf si on aime mesurer sa productivite a la longueur de son code ; 1 nouveau menu = 400 nouvelles lignes ^^.
