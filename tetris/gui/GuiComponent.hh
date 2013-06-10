#ifndef					__GUI_COMPONENT_HH__
# define				__GUI_COMPONENT_HH__

#include				<string>
#include				<vector>
#include                                <allegro5/allegro.h>
#include				<allegro5/allegro.h>
#include				<allegro5/allegro_font.h>
#include				<allegro5/allegro_ttf.h>
#include				"Vector3d.hh"
#include				"OptionManager.hpp"

class					GuiComponent
{
public:
  GuiComponent();
  virtual ~GuiComponent();
  void					setPosition(Vector3d const & pos);
  Vector3d				&getPosition();
  void					setVisible(bool val);
  virtual void				draw(Vector3d *position = NULL);
  virtual void				event(ALLEGRO_EVENT *event);
  void					setParent(GuiComponent *parent);
  GuiComponent				*getParent() const;
  bool					isSelectable() const;
  virtual void				select(bool val);
  virtual void				attachOption(Option *option);
  virtual void				saveOptionValue();
  virtual void				importOptionValue();
  virtual void				setColor(ALLEGRO_COLOR color);
  void					setId(int id);
  int					getId() const;
protected:
  bool					visible_;
  GuiComponent				*parent_;
  bool					selectable_;
  Option				*option_;
  ALLEGRO_COLOR				color_;
  Vector3d				position_;
  int					id_;
};

#endif					// __GUI_COMPONENT_HH__
