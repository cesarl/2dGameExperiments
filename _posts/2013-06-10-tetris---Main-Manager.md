---
layout: post
title: "Tetris | Isaac - Main Manager"
description: "Descrition du Manager principal"
category: Tetris, Isaac
tags: [V1, Tetris, Allegro5, c++, singleton pattern, manager]
---
{% include JB/setup %}

Qu'entendre par Main Manager ?
Tout simplement l'entite qui a pour tache la gestion de tous les autres managers.

Cet article sera court, car il y a peu a dire.
Des articles specifiques seront consacres a chaque sous managers. Le but de ce post est simplement de soulever quelques remarques qui me semble importantes.

Beaucoup de mes managers sont appelles a l'aide de singleton.
Par consequent ils sont initialises de maniere statique, a la compilation. Or l'ordre de compilation n'est definit par l'utilisateur. Nous ne pouvons donc pas savoir quel singleton sera initialise avec quel autre.
Dans le cas d'interdependance entre les singletons, cela peu poser quelques problemes.

Alexandrescu explique tres bien ce probleme dans __Modern C++ design generic patterns applied__, section 6.2.

> The compiler performs static initialization before the very first assembly statement of the program gets executed. (Usually, static initializers are right in the file containing the executable program, so loading is initializing.)
> On the other hand, C++ does not define the order of initialization for dynamically initialized objects found in different translation units, which is a major source of trouble. (A translation unit is, roughly speaking, a com-pilable C++ source file.)

De plus, jusqu'ici, je procedais (betement) a l'initialisation des singleton dans leur constructeurs, ce qui amene encore plus de problemes.
Je prends ici l'exemple d'Allegro, mais ce probleme peut concerner beaucoup d'autre bibliotheque - j'ai eu le meme probleme sur OpenGl par exemple.
Allegro doit initialise ``al_init`` avant d'utiliser certain de ses plugin, tels que celui pour le images par exemple (``al_init_image_addon()``). Par consequent, les singleteon etant initialises de maniere statique et selon un ordre qui nous est inconnu, il se peut que le plugin de bitmap soit initialises avant Allegro.
Si une telle situation se produit, le  compilateur ne rencontrera aucune erreur, mais il se peut que le fonctionnement du programme en soit affecte, et nous n'aurons alors que tres peu de moyen de determiner d'ou vien l'erreur.
Ce probleme est le meme pour la destruction des objets.

Il est donc important d'initialiser les singletons selon un certain ordre.
C'est a cela que sert le MainManager.

Tout les constructeurs et destructeurs des managers sont vides, cependant ils ont tous une methode ``initialize`` et ``uninitialize``. Ainsi, au lancement du programe, nous appelons la methode initialize du Main Manager qui se charge d'initialiser, dans l'ordre les differents manager. Pareil, a la fin du programme pour la deinitialisation.

Voila, c'est a peut pres tout ce qu'il y a a dire sur le MainManager !