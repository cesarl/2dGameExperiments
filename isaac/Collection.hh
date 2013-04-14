#ifndef				__COLLECTION_HH__
# define			__COLLECTION_HH__

#include			<vector>
#include			<string>
#include			<fstream>
#include			<ios>
#include			"Entity.hh"
#include			"ComponentTypes.hh"

template			<typename T>
class				Collection
{
public:
  Collection();
  virtual ~Collection();
  bool				save(std::string const & path, std::string const & name, int x, int y);
  bool				load(std::string const & path, std::string const & name, int x, int y);
  virtual void			generate(int seed = 0) = 0;
  void				clear();
  void				update(ALLEGRO_EVENT *event);
  void				draw(ALLEGRO_EVENT *event);
  std::vector<Entity*>		*getSelection(int x, int y, int w = 0, int h = 0);
  std::vector<Entity*>		*getSelection(Entity *entity);
protected:
  std::vector<T*>		go_;		// game object : pnj, weapons, objects
  std::vector<Entity*>		selection_;
};

#endif				// __COLLECTION_HH__
