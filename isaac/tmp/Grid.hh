#ifndef				__GRID_HH__
# define			__GRID_HH__

#include			<list>
#include			<vector>
#include			<map>
#include			"Entity.hh"
#include			"ComponentTypes.hh"

class				Grid
{
public:
  Grid(int cellSize = 100);
  ~Grid();
  void				update();
  void				add(Entity *entity);
  void				remove(Entity *entity);
  void				clear();
private:
  int				cellSize_;
  int				height_;
  int				width_;
  int				maxWidth_;
  std::map< int, std::list<Entity*> > list_;
  typedef			std::map < int, std::list<Entity*> >::iterator t_cell_iter;
  typedef			std::list<Entity*>::iterator t_iter;
};

#endif				// __GRID_HH__
