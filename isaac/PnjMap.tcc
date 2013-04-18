#include			"PnjMap.hh"

template			<typename T>
PnjMap<T>::PnjMap() :
  Collection<T>(1)
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
  Pnj				*tmp;

  if (seed)
    srand(seed);
  else
    srand(time(0));
  nb = rand() % 50 + 1;
  i = 0;
  while (i < nb)
    {
      tmp = new Pnj;
      tmp->generate(seed);
      POSITION(tmp)->setPos(rand() % 1000, rand() % 600);
      this->go_.push_back(tmp);
      ++i;
    }
}
