#ifndef					__IMAGE_HH__
# define				__IMAGE_HH__

#include				<allegro5/allegro.h>
#include				"Resource.hh"
#include				"SmartPointer.hpp"
#include				"SmartPointerPolicies.hpp"

class					Image : public Resource
{
public:
  Image(ALLEGRO_BITMAP *bmp) :
    Resource(),
    bmp_(bmp)
  {};

  Image() :
    Resource(),
    bmp_(NULL)
  {};

  void					sayHello() const
  {
    std::cout << "Hello I'm an image" << std::endl;
  }

  virtual ~Image()
  {};
private:
  ALLEGRO_BITMAP			*bmp_;
};

typedef					SmartPtr<Image, InternalRef> ImagePtr;

#endif					// __IMAGE_HH__
