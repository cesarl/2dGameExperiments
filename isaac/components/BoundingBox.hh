#ifndef					__BOUNDING_BOX_HH__
# define				__BOUNDING_BOX_HH__

#include				"Component.hh"
#include				"Entity.hh"

class					BoundingBox : public AComponent
{
public:
  BoundingBox(Entity *entity);
  virtual ~BoundingBox();
  virtual void				update(double time = 0);
  virtual void				draw();
  void					setWidth(int width);
  int					getWidth() const;
  void					setHeight(int height);
  int					getHeight() const;
  bool					collide(Entity *o) const;
  void					setDimension(int width, int height);
  bool					isCollidable() const;
  void					setCollidable(bool val);
private:
  int					width_;
  int					height_;
  bool					collidable_;
};

#endif					// __BOUNDING_BOX_HH__
