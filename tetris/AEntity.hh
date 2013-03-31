#ifndef					__AENTITY_HH__
# define				__AENTITY_HH__

class					AEntity
{
public:
  AEntity();
  virtual ~AEntity();
  void					setX(float x);
  void					setY(float y);
  void					setPos(float x, float y);
  void					setWidth(float width, float height);
  float					getX() const;
  float					getY() const;
  float					getWidth() const;
  float					getHeight() const;
private:
  float					x_;
  float					y_;
  float					width_;
  float					height_;
};

#endif					// __AENTITY_HH__
