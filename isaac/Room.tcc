#include			"Room.hh"

template <typename T>
Room<T>::Room() :
  Collection<T>(),
  width_(20),
  height_(10)
{
}

template <typename T>
Room<T>::~Room()
{}

template <typename T>
void				Room<T>::generate(int seed)
{
  int				y;
  int				x;
  Decor				*tmp;

  y = 0;
  while (y < this->height_)
    {
      x = 0;
      while (x < this->width_)
	{
	  tmp = new Decor;
	  tmp->generate(seed);
	  this->map_[y][x] = tmp;
	  this->go_.push_back(tmp);
	  POSITION(tmp)->setPos(x * CELL_SIZE, y * CELL_SIZE);
	  ++x;
	}
      ++y;
    }
}
