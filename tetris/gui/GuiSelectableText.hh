#ifndef					__GUI_SELECTABLE_TEXT_HH__
# define				__GUI_SELECTABLE_TEXT_HH__

#include				"GuiSelectable.hh"
#include				"GuiText.hh"

class					GuiSelectableText : public GuiSelectable
{
public:
  GuiSelectableText();
  virtual ~GuiSelectableText();
  void					setupText(std::string const & val, ALLEGRO_FONT *font);
  GuiText				*getText();
  virtual void				draw(Vector3d *position = NULL);
  virtual void				attachOption(Option *option);
  virtual void				select(bool val);
  virtual void				setColor(ALLEGRO_COLOR color);
private:
  GuiText				text_;
};

#endif					// __GUI_SELECTABLE_TEXT_HH__
