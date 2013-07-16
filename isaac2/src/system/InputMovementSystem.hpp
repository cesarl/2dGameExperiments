#ifndef				__IPT_MOVEMENT_SYSTEM_HPP__
# define			__IPT_MOVEMENT_SYSTEM_HPP__

#include			"System.hpp"
#include			"ComponentManager.hpp"
#include			"Components.hpp"
#include			"InputSystem.hpp"

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
  }


  virtual void			update(unsigned int entity, float time, const ALLEGRO_EVENT &)
  {
    InputMovement		*input = ComponentManager::getInstance().getComponent<InputMovement>(entity);
    Velocity			*vel = ComponentManager::getInstance().getComponent<Velocity>(entity);
    InputSystem			*sys = SystemManager::getInstance().getSystem<InputSystem>();

    if (!sys)
      return;

    if (sys->isDown(ALLEGRO_KEY_W))
      vel->velocity.y += input->speed * time;
    if (sys->isDown(ALLEGRO_KEY_S))
      vel->velocity.y -= input->speed * time;
    if (sys->isDown(ALLEGRO_KEY_A))
      vel->velocity.x -= input->speed * time;
    if (sys->isDown(ALLEGRO_KEY_D))
      vel->velocity.x += input->speed * time;
  }

private:
};

#endif				// __IPT_MOVEMENT_SYSTEM_HPP__
