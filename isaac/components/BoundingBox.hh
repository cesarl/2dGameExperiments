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
  int					getMarginX() const;
  int					getMarginY() const;
  bool					collide(Entity *o) const;
  void					setDimension(int width, int height);
  bool					isCollidable() const;
  void					setCollidable(bool val);
  void					setMargin(int x, int y);
  void					setMarginX(int x);
  void					setMarginY(int y);
  int					getX() const;
  int					getY() const;
  int					getXX() const;
  int					getYY() const;
  int					getCenterX() const;
  int					getCenterY() const;
private:
  int					width_;
  int					height_;
  bool					collidable_;
  int					marginX_;
  int					marginY_;
};

#endif					// __BOUNDING_BOX_HH__
