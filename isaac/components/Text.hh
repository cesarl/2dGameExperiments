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
  virtual void				serialize(std::ofstream &file);
  virtual void				unserialize(std::ifstream &file);
  void					setFont(std::string const & imagePath, int size);
  void                                  operator=(std::string const & str);
  void                                  operator+=(std::string const & str);
public:
  ALLEGRO_FONT				*font;
  ALLEGRO_COLOR				color;
  int					align;
  std::string				text;
  std::string				fontPath;
};

#endif					// __TEXT_HH__
