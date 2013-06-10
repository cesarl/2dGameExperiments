#ifndef					__GUI_NBR_HH__
# define				__GUI_NBR_HH__

#include				<sstream>
#include				"GuiComponent.hh"

class					GuiNumber : public GuiComponent
{
public:
  GuiNumber(int val = 0);
  virtual ~GuiNumber();
  void					operator=(int val);
  void					operator+=(int val);
  void					operator-=(int val);
  void					operator/=(int val);
  void					operator*=(int val);
  void					setFont(ALLEGRO_FONT *font);
  virtual void				draw(Vector3d *position = NULL);
  void					updateStr();
  int					getVal() const;
  virtual void				saveOptionValue();
  virtual void				importOptionValue();
protected:
  int					val_;
  ALLEGRO_FONT				*font_;
  std::string				strVal_;
};

#endif					// __GUI_NBR_HH__
