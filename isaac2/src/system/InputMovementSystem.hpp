#ifndef				__IPT_MOVEMENT_SYSTEM_HPP__
# define			__IPT_MOVEMENT_SYSTEM_HPP__

#include			"System.hpp"
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
	InputMovement		*input = entity.getComponent<InputMovement>();
    Velocity			*vel = entity.getComponent<Velocity>();
    Rotation			*rotation = entity.getComponent<Rotation>();
    Sprite  			*sprite = entity.getComponent<Sprite>();
    InputSystem			*sys = SystemManager::getInstance().getSystem<InputSystem>();

    if (!sys)
      return;

    if (sys->isDown(ALLEGRO_KEY_W))
      {
	vel->velocity.y += input->speed * time;
	sprite->animation = ResourceManager::getInstance().get<AnimationMedia>("herosWalkFront.anim");
      }
    if (sys->isDown(ALLEGRO_KEY_S))
      {
	vel->velocity.y -= input->speed * time;
	sprite->animation = ResourceManager::getInstance().get<AnimationMedia>("herosWalkBack.anim");
      }
    if (sys->isDown(ALLEGRO_KEY_A))
      {
	vel->velocity.x -= input->speed * time;
	rotation->rotation.y = 0.0f;
	sprite->animation = ResourceManager::getInstance().get<AnimationMedia>("herosWalkSide.anim");
      }
    if (sys->isDown(ALLEGRO_KEY_D))
      {
	vel->velocity.x += input->speed * time;
	rotation->rotation.y = -180.0f;
	sprite->animation = ResourceManager::getInstance().get<AnimationMedia>("herosWalkSide.anim");
      }
    
  }

private:
};

#endif				// __IPT_MOVEMENT_SYSTEM_HPP__
