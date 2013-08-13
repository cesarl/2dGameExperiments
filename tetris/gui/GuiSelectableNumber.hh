#ifndef					__GUI_SELECTABLE_NBR_HH__
# define				__GUI_SELECTABLE_NBR_HH__

#include				"GuiSelectable.hh"
#include				"GuiNumber.hh"

class					GuiSelectableNumber : public GuiSelectable
{
public:
  GuiSelectableNumber();
  virtual ~GuiSelectableNumber();
  void					setupNumber(int val, ALLEGRO_FONT *font);
  GuiNumber				*getNumber();
  int					getVal() const;
  virtual void				draw(Vector3d *position = NULL);
  virtual void				attachOption(Option *option);
  virtual void				select(bool val);
  virtual void				setColor(ALLEGRO_COLOR color);
protected:
  GuiNumber				nbr_;
};

#endif					// __GUI_SELECTABLE_NBR_HH__
