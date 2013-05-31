#include				"Decor.hh"
#include				"ComponentTypes.hh"

Decor::Decor() : Entity()
{}

Decor::~Decor()
{}

void					Decor::serialize(std::ofstream *file)
{
  int					x;
  int					y;
  int					r;
  Position				*position;
  Rotation				*rotation;

  position = POSITION(this);
  rotation = ROTATION(this);

  x = (int)(position->x);
  y = (int)(position->y);
  r = (int)(rotation->angle * 180 / M_PI);

  file->write(reinterpret_cast<const char *>(&this->seed_), sizeof(this->seed_));
  file->write(reinterpret_cast<const char *>(&x), sizeof(x));
  file->write(reinterpret_cast<const char *>(&y), sizeof(y));
  file->write(reinterpret_cast<const char *>(&r), sizeof(r));
}

void					Decor::unserialize(std::ifstream *file)
{
  int				posx;
  int				posy;
  int				rot;
  int				seed;

  file->read(reinterpret_cast<char*>(&seed), sizeof(int));
  file->read(reinterpret_cast<char*>(&posx), sizeof(int));
  file->read(reinterpret_cast<char*>(&posy), sizeof(int));
  file->read(reinterpret_cast<char*>(&rot), sizeof(int));
  this->generate(seed);
  POSITION(this)->setPos(posx, posy);
  ROTATION(this)->angle = rot * M_PI / 180;
}

void					Decor::generate(int seed)
{
  if (seed != 0)
    this->seed_ = seed;
  srand(this->seed_);
  IMAGE(this)->setBitmap("assets/imgs/decor.png");
  if (this->seed_ != -1 && rand() % 6 != 0)
    {
      SPRITE(this)->config(4, 64, 64, 9, 0, 9, 0);
      BOUNDING_BOX(this)->setCollidable(false);
      *TEXT(this) = "ground";
    }
  else
    {
      SPRITE(this)->config(4, 64, 64, 4, 0, 4, 0);
      COLLISION_TYPE(this)->setType(FIX_GO);
      *TEXT(this) = "wall";
    }
  BOUNDING_BOX(this)->setDimension(64, 64);
  FORCE_RESISTANCE(this)->setResistance(-1);
  COLLISION_TYPE(this)->setType(FIX_GO);
}
