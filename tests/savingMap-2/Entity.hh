#ifndef				__ENTITY_HH__
# define			__ENTITY_HH__

#include			<allegro5/allegro.h>
#include			<allegro5/allegro_native_dialog.h>
#include			<allegro5/allegro_primitives.h>

class				Entity
{
public:
  Entity(int x = 0, int y = 0, int radius = 10);
  ~Entity();
public:
  void				move();
  void				draw();
  int				getX() const;
  int				getY() const;
  void				setX(int x);
  void				setY(int y);
  int				getRadius() const;
  void				setRadius(int radius);
  ALLEGRO_COLOR			getColor() const;
  int				getHexColor() const;
  void				setColor(ALLEGRO_COLOR color);
  bool				getVisible() const;
  void				setVisible(bool visible);
  void				setHexColor(int color);
private:
  int				x_;
  int				y_;
  int				radius_;
  bool				visible_;
  int				hexColor_;
  ALLEGRO_COLOR			color_;
private:
  void				p_hexColorToAlColor();
};

#endif				// __ENTITY_HH__
