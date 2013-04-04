#ifndef					__CONTENT_COMPONENT_IMAGE_HH__
# define				__CONTENT_COMPONENT_IMAGE_HH__

#include				"ImageManager.hh"
#include				"AContentComponent.hh"

class					ContentComponentImage : public AContentComponent
{
public:
  ContentComponentImage();
  ContentComponentImage(std::string const & imagePath);
  ContentComponentImage(ALLEGRO_BITMAP *image);
  void					setBitmap(std::string const & imagePath);
  void					setBitmap(ALLEGRO_BITMAP *image);
  virtual ~ContentComponentImage();
  virtual void				update(Entity *entity, ALLEGRO_EVENT *event);
  virtual void				draw(Entity *entity);
protected:
  ALLEGRO_BITMAP			*bitmap_;
};

#endif					// __CONTENT_COMPONENT_IMAGE_HH__
