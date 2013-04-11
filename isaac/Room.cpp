#include			"Room.hh"

Room::Room() :
  width_(20),
  height_(10)
{
}

Room::~Room()
{}

bool				Room::save(std::string const & path, std::string const & name, int x, int y)
{
  (void)path;
  (void)name;
  (void)x;
  (void)y;
  return false;
}

bool				Room::load(std::string const & path, std::string const & name, int x, int y)
{
  (void)path;
  (void)name;
  (void)x;
  (void)y;
  return false;
}

void				Room::generate()
{
  int				y;
  int				x;

  // if (this->map_)
  //   this->clear();

  HEROS(&this->heros_);
  POSITION(&this->heros_)->setPos(300, 300);
  SPRITE(&this->heros_)->config(8, CELL_SIZE, CELL_SIZE, 8, 8, 8, 0.12);
  IMAGE(&this->heros_)->setBitmap("assets/imgs/heros.png");
  y = 0;
  while (y < this->height_)
    {
      x = 0;
      while (x < this->width_)
	{
	  SPRITE(&this->map_[y][x])->config(4, CELL_SIZE, CELL_SIZE, 0, 0, 0, 0);
	  IMAGE(&this->map_[y][x])->setBitmap("assets/imgs/decor.png");
	  POSITION(&this->map_[y][x])->setPos(x * CELL_SIZE, y * CELL_SIZE);
	  if (x == 0 || x == this->width_ - 1 || y == this->height_ - 1)
	    SPRITE(&this->map_[y][x])->config(4, CELL_SIZE, CELL_SIZE, 9, 0, 9, 0);
	  else if (y == 0)
	    SPRITE(&this->map_[y][x])->config(4, CELL_SIZE, CELL_SIZE, 4, 0, 4, 0);
	  ++x;
	}
      ++y;
    }
}

void				Room::clear()
{
  // int				y;
  // int				x;

  // y = 0;
  // while (y < this->height_)
  //   {
  //     x = 0;
  //     while (x < this->width_)
  // 	{
  // 	  if (this->map_[y][x])
  // 	    delete this->map_[y][x];
  // 	  ++x;
  // 	}
  //     ++y;
  //   }
}

void				Room::update(ALLEGRO_EVENT *event)
{
  int				y;
  int				x;

  y = 0;
  while (y < this->height_)
    {
      x = 0;
      while (x < this->width_)
  	{
	  this->map_[y][x].update();
  	  ++x;
  	}
      ++y;
    }
  this->heros_.update();
  (void)event;
}

void				Room::draw(ALLEGRO_EVENT *event)
{
  int				y;
  int				x;

  y = 0;
  while (y < this->height_)
    {
      x = 0;
      while (x < this->width_)
  	{
	  this->map_[y][x].draw();
  	  ++x;
  	}
      ++y;
    }
  this->heros_.draw();
  (void)event;
}
