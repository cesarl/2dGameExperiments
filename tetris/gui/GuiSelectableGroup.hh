#ifndef					__GUI_SELECTABLE_GROUP_HH__
# define				__GUI_SELECTABLE_GROUP_HH__

#include				"GuiSelectable.hh"

class					GuiSelectableGroup : public GuiSelectable
{
public:
  GuiSelectableGroup();
  virtual ~GuiSelectableGroup();
  void					clear();
  void					pushComponent(GuiComponent *component);
  virtual void				draw(Vector3d *position = NULL);
  void					setHorizontal(bool val);
  virtual void				event(ALLEGRO_EVENT *event);
  void					selectNext();
  void					selectPrev();
  void					selectFirst();
  virtual void				setColor(ALLEGRO_COLOR color);
private:
  bool					horizontal_;
  std::vector<GuiComponent*>		sellist_;
  std::vector<GuiComponent*>		list_;
  std::vector<GuiComponent*>::iterator	selected_;
  typedef std::vector<GuiComponent*>::iterator t_iter;
};

#endif					// __GUI_SELECTABLE_GROUP_HH__
