#ifndef					__IMAGE_HH__
# define				__IMAGE_HH__

#include				<string>
#include				"Component.hh"
#include				"Entity.hh"
#include				"ImageManager.hh"

class					Image : public AComponent
{
public:
  Image(Entity *entity);
  virtual ~Image();
  virtual void				update(double time = 0);
  virtual void				draw();
  void					setBitmap(std::string const & imagePath);
  void					setBitmap(ALLEGRO_BITMAP *image);
public:
  ALLEGRO_BITMAP			*bitmap;
};

#endif					// __IMAGE_HH__
