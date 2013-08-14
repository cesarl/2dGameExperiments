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
    require<Rotation>();
    require<Sprite>();
    require<Velocity>();
  }


  virtual void			update(EntityData &entity, float time, const ALLEGRO_EVENT &)
  {
    InputMovement		*input = ComponentManager::getInstance().getComponent<InputMovement>(entity);
    Velocity			*vel = ComponentManager::getInstance().getComponent<Velocity>(entity);
    Rotation			*rotation = ComponentManager::getInstance().getComponent<Rotation>(entity);
    Sprite			*sprite = ComponentManager::getInstance().getComponent<Sprite>(entity);
    InputSystem			*sys = SystemManager::getInstance().getSystem<InputSystem>();

    if (!sys)
      return;

    if (sys->isDown(ALLEGRO_KEY_W))
      {
	vel->velocity.y += input->speed * time;
	sprite->animation = ResourceManager::getInstance().get<Animation>("herosWalkFront.anim");
      }
    if (sys->isDown(ALLEGRO_KEY_S))
      {
	vel->velocity.y -= input->speed * time;
	sprite->animation = ResourceManager::getInstance().get<Animation>("herosWalkBack.anim");
      }
    if (sys->isDown(ALLEGRO_KEY_A))
      {
	vel->velocity.x -= input->speed * time;
	rotation->rotation.y = 0.0f;
	sprite->animation = ResourceManager::getInstance().get<Animation>("herosWalkSide.anim");
      }
    if (sys->isDown(ALLEGRO_KEY_D))
      {
	vel->velocity.x += input->speed * time;
	rotation->rotation.y = -180.0f;
	sprite->animation = ResourceManager::getInstance().get<Animation>("herosWalkSide.anim");
      }
    
  }

private:
};

#endif				// __IPT_MOVEMENT_SYSTEM_HPP__
