---
layout: post
title: "Tetris | Isaac - Option Manager"
description: "Descrition de l'option manager"
category: Tetris, Isaac
tags: [V1, Tetris, Isaac, Allegro5, c++, manager, option manager]
---
{% include JB/setup %}

J'evoquais dans un precedent article le probleme que me posait les Scenes quand a la communication de donnes entre elles. J'avais alors opte pour une solution degoutante. J'appelais la methode d'une scene en lui passant un ``void *`` en parametre que je castait ensuite.

Au cours d'autre developpement qui on suivit cette implementation, je me suis penche sur d'autre problematiques, dont la GUI et les menus. (Je consacrerais un article a la nouvelle implementation de la GUI).

Prenons l'exemple de 2 scenes :
- Une scene de creation de partie contenant un menu proposant au joueur de creer un nouvelle partie.
 - Taille de la carte
 - Nombre de pnj
- Une scene de jeu avec une carte de la taille selectionnees dans la scene precedente ainsi que le meme nombre de PNJ.

Il faudra que la scene de jeu soit au courant des valeurs definit dans la scene de paramettrage de la partie.

L'ancienne solution que je proposait consistait a passer des ``void*`` en argument et de les caster ensuite.

L'option manager va servir ici a stocker des informations partagees entre plusieurs sections du programme - dans l'exemple ci-dessus, les valeurs seront partagees entre differentes scenes.

Nous avons  un ``OptionManager`` sous la forme de singleton.
Ce dernier ne contient rien d'autre qu'une ``std::map`` avec un ``std::string`` en clef et un pointer sur ``Option`` en valeur.

L'OptionManager a plusieurs fontions membres :

**Creation d'une option**

    template				<typename T>
    void				create(std::string key, T const & value)
    {
        Option				*tmp;
        t_iter				it;

        it = this->list_.find(key);
        if (it != this->list_.end())
          return;
        tmp = new OptionValue<T>(value);
        this->list_.insert(t_pair(key, tmp));
      }


**Modification de la valeur d'une option**

    template                              <typename T>
    void                                  setOption(std::string key, const T & value)
    {
      t_iter                              it;

      it = this->list_.find(key);
      if (it != this->list_.end())
        dynamic_cast<OptionValue<T>*>(it->second)->setValue(value);
      else
        this->create<T>(key, value);
    }

**Acces a une option**

    template				<typename T>
    OptionValue<T>			*getOption(std::string key)
    {
      t_iter				it;
      OptionValue<T>			*value;

      it = this->list_.find(key);
      if (it != this->list_.end())
        {
          value = dynamic_cast<OptionValue<T>*>(it->second);
          return value;
        }
      return NULL;
    }

La class ``Option`` n'est qu'une interface vide.

La class ``OptionValue`` herite d'option et est templatee.
Elle a un simple attribut qui contient sa valeur et qui est du type passe en argument de template.

    template				<typename T>
    class				OptionValue : public Option
    {
    public:
      OptionValue<T>(T val) :
      Option(),
        val_(val)
      {}

      virtual ~OptionValue()
      {}

      T const				&getValue() const
      {
        return this->val_;
      }

      void				setValue(T const & val)
      {
        this->val_ = val;
      }
    private:
      T					val_;
    };

L'utilisation est ensuite tres simple. Une fois option de type T cree, associee a une clef X. Il est possible d'acceder a sa valeur depuis n'importe ou.

Je me sert de cet OptionManager pour beaucoup de fonctionnalites dans mes projets (peut-etre en fais-je un emploi abusif). Par exemple, je m'en suis servit sur un projet en OpenGl ou l'interval de rafraishissement des inputs devait etre different selon les contexte (rapide en temps de jeu, plus lent dans les menus). Je m'en sert aussi pour passer des informations entre les scenes, tels que le score par exemple.
