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
  virtual void				serialize(std::ofstream *file);
  virtual void				unserialize(std::ifstream *file);
  void					setBitmap(std::string const & imagePath);
public:
  ALLEGRO_BITMAP			*bitmap;
  std::string				path;
};

#endif					// __IMAGE_HH__
