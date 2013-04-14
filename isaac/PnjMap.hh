#ifndef				__PNJ_MAP_HH__
# define			__PNJ_MAP_HH__

#include			"Collection.hh"

template			<typename T>
class				PnjMap : public Collection<T>
{
public:
  PnjMap();
  virtual ~PnjMap();
  virtual void			generate(int seed = 0);
private:
};

#endif				// __PNJ_MAP_HH__
