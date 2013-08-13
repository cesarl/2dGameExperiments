#ifndef				__IPT_SYSTEM_HPP__
# define			__IPT_SYSTEM_HPP__

#include			<map>
#include			"System.hpp"
#include			"ComponentManager.hpp"
#include			"Components.hpp"

class				InputSystem : public System
{
public:
  virtual ~InputSystem()
  {
    keysMap_.clear();
  }

  InputSystem()
  {}

  void				init()
  {
    require<NullCpt>();

    for (int i = ALLEGRO_KEY_A; i <= ALLEGRO_KEY_COMMAND; ++i)
      {
	keysMap_.insert(std::pair<int, bool>(i, false));
      }
  }


  virtual void			update(EntityData&, float, const ALLEGRO_EVENT &)
  {
  }

  bool				isDown(int key)
  {
    t_iter it = keysMap_.find(key);

    if (it == keysMap_.end())
      return false;
    return it->second;
  }

  virtual void			updateBegin(float, const ALLEGRO_EVENT &ev)
  {
    if (ev.type != ALLEGRO_EVENT_KEY_DOWN && ev.type != ALLEGRO_EVENT_KEY_UP)
      return;

    t_iter it = keysMap_.find(ev.keyboard.keycode);

    if (it == keysMap_.end())
      return;
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
      it->second = true;
    else if (ev.type == ALLEGRO_EVENT_KEY_UP)
      it->second = false;
  }

private:
  std::map<int, bool>		keysMap_;
  typedef std::map<int, bool>::iterator t_iter;
};

#endif				// __IPT_SYSTEM_HPP__
