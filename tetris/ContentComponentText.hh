#ifndef					__CONTENT_COMPONENT_TEXT_HH__
# define				__CONTENT_COMPONENT_TEXT_HH__

#include				"IContentComponent.hh"
#include				"FontManager.hh"
#include				"Entity.hh"

class					ContentComponentText : public IContentComponent
{
public:
  ContentComponentText();
  ContentComponentText(std::string const & fontPath, int size = 0);
  ContentComponentText(ALLEGRO_FONT *font);
  virtual ~ContentComponentText();
  virtual void				update(Entity *entity, ALLEGRO_EVENT *event);
  virtual void				draw(Entity *entity);
  void					setFont(std::string const & fontPath, int size = 0);
  void					setFont(ALLEGRO_FONT * font);
  void					setAlign(int align);
  void					setColor(ALLEGRO_COLOR color);
  void                                  operator=(std::string const & str);
  void                                  operator+=(std::string const & str);
private:
  ALLEGRO_FONT				*font_;
  int					align_;
  ALLEGRO_COLOR				color_;
  std::string				text_;
};

#endif					// __CONTENT_COMPONENT_TEXT_HH__
