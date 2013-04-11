#ifndef				__ROOM_HH__
# define			__ROOM_HH__

#include			<vector>
#include			<string>
#include			"Entity.hh"
#include			"ComponentTypes.hh"

#define				CELL_SIZE 64


class				Room
{
public:
  Room();
  ~Room();
  bool				save(std::string const & path, std::string const & name, int x, int y);
  bool				load(std::string const & path, std::string const & name, int x, int y);
  void				generate();
  void				clear();
  void				update(ALLEGRO_EVENT *event);
  void				draw(ALLEGRO_EVENT *event);
private:
  Entity			heros_;
  Entity			map_[10][20];	// map tile objets
  int				width_;		// nb of tiles hor
  int				height_;	// nb of tiles ver
  std::vector<Entity*>		go_;		// game object : heros, pnj, weapons, objects
};

#endif				// __ROOM_HH__
