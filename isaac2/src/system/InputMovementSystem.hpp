#ifndef				__IPT_MOVEMENT_SYSTEM_HPP__
# define			__IPT_MOVEMENT_SYSTEM_HPP__

#include			"System.hpp"
#include			"ComponentManager.hpp"
#include			"Components.hpp"

class				InputMovementSystem : public System
{
public:
  virtual ~InputMovementSystem()
  {}

  InputMovementSystem()
  {}

  void				init()
  {
    require<InputMovement>();
    require<Velocity>();
  }


  virtual void			update(unsigned int entity, float, const ALLEGRO_EVENT &ev)
  {
    InputMovement		*input = ComponentManager::getInstance().getComponent<InputMovement>(entity);
    Velocity			*vel = ComponentManager::getInstance().getComponent<Velocity>(entity);

    if (ev.type == ALLEGRO_EVENT_KEY_DOWN || ev.type == ALLEGRO_EVENT_KEY_UP)
      {
	std::cout << "prout " << std::endl;
	switch (ev.keyboard.keycode)
	  {
	  case ALLEGRO_KEY_W:
	    if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
	      input->up = true;
	    else if (ev.type == ALLEGRO_EVENT_KEY_UP)
	      input->up = false;
	    break;
	  case ALLEGRO_KEY_S:
	    if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
	      input->down = true;
	    else if (ev.type == ALLEGRO_EVENT_KEY_UP)
	      input->down = false;
	    break;
	  case ALLEGRO_KEY_A:
	    if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
	      input->left = true;
	    else if (ev.type == ALLEGRO_EVENT_KEY_UP)
	      input->left = false;
	    break;
	  case ALLEGRO_KEY_D:
	    if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
	      input->right = true;
	    else if (ev.type == ALLEGRO_EVENT_KEY_UP)
	      input->right = false;
	    break;
	  }
      }

    // std::cout << "lol" <<std::endl;
    if (input->up)
      vel->velocity.y += input->speed;
    if (input->down)
      vel->velocity.y -= input->speed;
    if (input->left)
      vel->velocity.x -= input->speed;
    if (input->right)
      vel->velocity.x += input->speed;

      
  }

  virtual void			updateBegin()
  {}

  virtual void			updateEnd()
  {}

private:
};

#endif				// __IPT_MOVEMENT_SYSTEM_HPP__
