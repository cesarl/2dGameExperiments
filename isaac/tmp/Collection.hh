#ifndef				__COLLECTION_HH__
# define			__COLLECTION_HH__

#include			<list>
#include			<string>
#include			<fstream>
#include			<ios>
#include			"Entity.hh"
#include			"ComponentTypes.hh"
#include			"DrawManager.hh"
#include			"Grid.hh"

template			<typename T>
class				Collection
{
public:
  Collection(int zindex = 0);
  virtual ~Collection();
  bool				save(std::string const & path, std::string const & name, int x, int y);
  bool				load(std::string const & path, std::string const & name, int x, int y);
  virtual void			generate(int seed = 0) = 0;
  void				clear();
  void				update(ALLEGRO_EVENT *event);
  void				draw(ALLEGRO_EVENT *event);
  std::list<Entity*>		*getSelection(int x, int y, int w = 0, int h = 0);
  std::list<Entity*>		*getSelection(Entity *entity);
  void				attachGrid(Grid *grid);
  void				attachDrawCollection(DrawCollection *drawCollection);
  void				setZIndex(int index);
  void				fillGrid();
  void				remove(Entity* entity);
  void				add(Entity* entity);
protected:
  Grid				*grid_;
  int				zindex_;
  std::list<T*>			go_;		// game object : pnj, weapons, objects
  std::list<Entity*>		selection_;
};

#endif				// __COLLECTION_HH__
