#ifndef					__SPRITE_MANAGER_H__
# define				__SPRITE_MANAGER_H__

#include				<list>
#include				<map>
#include				<string>
#include				<iostream>
#include				<sstream>
#include				"ImageManager.hh"

class					SpriteManager
{
public:
  ~SpriteManager();
  static SpriteManager			*getInstance();
  ALLEGRO_FONT				*load(std::string const & path, int size);
  void					erase(std::string const & path, int size);
  ALLEGRO_FONT				*get(std::string const & path, int size);
private:
  SpriteManager();			// private ctor because of singleton pattern
  std::map<std::string, ALLEGRO_FONT*> collection_;
  typedef std::map<std::string, ALLEGRO_FONT*>::iterator t_iter;
  typedef std::pair<std::string, ALLEGRO_FONT*> t_pair;
};

#endif					// __FONT_MANAGER_H__
