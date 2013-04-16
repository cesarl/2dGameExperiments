#include			"PnjMap.hh"

template			<typename T>
PnjMap<T>::PnjMap() :
  Collection<T>()
{
}

template			<typename T>
PnjMap<T>::~PnjMap()
{}

template			<typename T>
void				PnjMap<T>::generate(int seed)
{
  int				nb;
  int				i;
  Entity			*tmp;

  if (seed)
    srand(seed);
  else
    srand(time(0));
  nb = rand() % 50 + 1;
  i = 0;
  while (i < nb)
    {
      tmp = new Entity;
      POSITION(tmp)->setPos(rand() % 1000, rand() % 600);
      SPRITE(tmp)->config(8, 64, 64, 8, 8, 8, 0.12);
      IMAGE(tmp)->setBitmap("assets/imgs/mummy.png");
      FORCE_RESISTANCE(tmp)->setResistance(1);
      MOVE(tmp)->setFriction(0.07, 0.07);
      BOUNDING_BOX(tmp)->setDimension(30, 30);
      BOUNDING_BOX(tmp)->setMargin(17, 17);
      this->go_.push_back(tmp);
      ++i;
    }
}
