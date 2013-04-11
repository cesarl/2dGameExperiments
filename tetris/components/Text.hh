#ifndef					__TEXT_HH__
# define				__TEXT_HH__

#include				<string>
#include				"Component.hh"
#include				"Entity.hh"
#include				"FontManager.hh"

class					Text : public AComponent
{
public:
  Text(Entity *entity);
  virtual ~Text();
  virtual void				update(double time = 0);
  virtual void				draw();
  void					setFont(std::string const & imagePath, int size);
  void					setFont(ALLEGRO_FONT *font);
  void                                  operator=(std::string const & str);
  void                                  operator+=(std::string const & str);
public:
  ALLEGRO_FONT				*font;
  ALLEGRO_COLOR				color;
  int					align;
  std::string				text;
};

#endif					// __TEXT_HH__
