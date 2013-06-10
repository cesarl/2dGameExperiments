#ifndef					__GUI_SELECTABLE_HH__
# define				__GUI_SELECTABLE_HH__

#include				"GuiComponent.hh"

class					GuiSelectable : public GuiComponent
{
public:
  GuiSelectable();
  virtual ~GuiSelectable();
  virtual void				select(bool val);
  virtual void				pressed();
  void					setPressAction(void (*function)(GuiComponent *gui));
  void					setSelectAction(void (*function)(GuiComponent *gui));
  void					setUnselectAction(void (*function)(GuiComponent *gui));
  void					setDeleteAction(void (*function)(GuiComponent *gui));
  virtual void				event(ALLEGRO_EVENT *event);
protected:
  bool					selected_;
  void					(*pressAction_)(GuiComponent *gui);
  void					(*selectAction_)(GuiComponent *gui);
  void					(*unselectAction_)(GuiComponent *gui);
  void					(*deleteAction_)(GuiComponent *gui);
};

#endif					// __GUI_SELECTABLE_HH__
