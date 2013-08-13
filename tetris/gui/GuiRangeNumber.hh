#ifndef					__GUI_RANGE_NBR_HH__
# define				__GUI_RANGE_NBR_HH__

#include				"GuiSelectableNumber.hh"

class					GuiRangeNumber : public GuiSelectableNumber
{
public:
  GuiRangeNumber();
  ~GuiRangeNumber();
  void					setBounds(int min, int max);
  virtual void				event(ALLEGRO_EVENT *event);
  void					increment(int n);
private:
  int					min_;
  int					max_;
};

#endif					// __GUI_RANGE_NBR_HH__
