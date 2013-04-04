#ifndef					__ENTITY_HH__
# define				__ENTITY_HH__

#include				<allegro5/allegro.h>
#include				<allegro5/allegro_image.h>
#include				<list>
#include				"AContentComponent.hh"
#include				"ContentComponentTypes.hh"

class					AContentComponent;

class					Entity
{
public:
  Entity();
  Entity(AContentComponent *content);
  ~Entity();
  void					update(ALLEGRO_EVENT *event = NULL);
  void					draw();
  void					setPos(float x, float y);
  void					setX(float x);
  void					setY(float y);
  void					setWidth(float width);
  void					setHeight(float height);
  void					setVisible(bool visible);
  float					getX() const;
  float					getY() const;
  float					getWidth() const;
  float					getHeight() const;
  void					setContentComponent(AContentComponent *content, unsigned int priority = 0);
  AContentComponent			*getContentComponent(e_contentComponentType type = ALL_TYPE) const;
  bool					getVisible() const;
  // void					deleteContentComponent();
  typedef std::list<AContentComponent*>::iterator t_iter;
  typedef std::list<AContentComponent*>::const_iterator t_const_iter;
private:
  float					x_;
  float					y_;
  float					width_;
  float					height_;
  bool					visible_;
  std::list<AContentComponent*>		content_;
};

#endif					// __ENTITY_HH__
