#ifndef					__IMAGE_HH__
# define				__IMAGE_HH__

#include				<allegro5/allegro.h>
#include				"Resource.hh"

class					Image : public Resource
{
public:
  Image(ALLEGRO_BITMAP *bmp) :
    Resource(),
    bmp_(bmp)
  {};

  virtual ~Image()
  {};
private:
  ALLEGRO_BITMAP			*bmp_;
};

#endif					// __IMAGE_HH__
