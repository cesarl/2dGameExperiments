#ifndef					__GUI_TEXT_HH__
# define				__GUI_TEXT_HH__

#include				"GuiComponent.hh"

class					GuiText : public GuiComponent
{
public:
  GuiText(std::string const & val = "");
  virtual ~GuiText();
  void					operator=(std::string const & str);
  void					operator+=(std::string const & str);
  void					setFont(ALLEGRO_FONT *font);
  virtual void				draw(Vector3d *position = NULL);
  virtual void				saveOptionValue();
  virtual void				importOptionValue();
private:
  std::string				val_;
  ALLEGRO_FONT				*font_;
};

#endif					// __GUI_TEXT_HH__
