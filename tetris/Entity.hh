#ifndef					__ENTITY_HH__
# define				__ENTITY_HH__

#include				<allegro5/allegro.h>
#include				<allegro5/allegro_image.h>
#include				"IContentComponent.hh"

class					IContentComponent;

class					Entity
{
public:
  Entity();
  Entity(IContentComponent *content);
  ~Entity();
  void					update(ALLEGRO_EVENT *event = NULL);
  void					draw();
  void					setPos(float x, float y);
  void					setX(float x);
  void					setY(float y);
  void					setWidth(float width);
  void					setHeight(float height);
  float					getX() const;
  float					getY() const;
  float					getWidth() const;
  float					getHeight() const;
  void					setContentComponent(IContentComponent *content);
  IContentComponent			*getContentComponent() const;
  void					deleteContentComponent();
private:
  IContentComponent			*content_;
  float					x_;
  float					y_;
  float					width_;
  float					height_;
};

#endif					// __ENTITY_HH__
