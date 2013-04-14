#ifndef				__ROOM_HH__
# define			__ROOM_HH__

#include			"Collection.tcc"
#include			"Decor.hh"

#define				CELL_SIZE 64

template			<typename T>
class				Room : public Collection<T>
{
public:
  Room();
  virtual ~Room();
  virtual void			generate(int seed = 0);
private:
  Entity*			map_[10][20];	// map tile objets
  int				width_;		// nb of tiles hor
  int				height_;	// nb of tiles ver
};

#endif				// __ROOM_HH__
