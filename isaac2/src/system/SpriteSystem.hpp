#ifndef				__SPRITE_SYSTEM_HPP__
# define			__SPRITE_SYSTEM_HPP__

#include			"System.hpp"
#include			"ComponentManager.hpp"
#include			"Components.hpp"

class				SpriteSystem : public System
{
public:
  virtual ~SpriteSystem(){};
  SpriteSystem() : System()
  {}

  virtual void			init()
  {
    require<Sprite>();
    require<Position>();
    require<Rotation>();
    require<Scale>();
    require<Color>();
  }

  virtual void			update(EntityData &entity, float time, const ALLEGRO_EVENT &ev)
  {
    Sprite			*sprite = ComponentManager::getInstance().getComponent<Sprite>(entity);
    Position			*pos = ComponentManager::getInstance().getComponent<Position>(entity);
    Rotation			*rot = ComponentManager::getInstance().getComponent<Rotation>(entity);
    Scale			*scale = ComponentManager::getInstance().getComponent<Scale>(entity);
    Color			*color = ComponentManager::getInstance().getComponent<Color>(entity);

    glPushMatrix();
    
    glTranslatef(pos->position.x, pos->position.y, pos->position.z);

    glScalef(scale->scale.x, scale->scale.y, scale->scale.z);

    glTranslatef(rot->axe.x,
		 rot->axe.y,
		 rot->axe.z);

    glRotatef(rot->rotation.x, 1.0f, 0.0f, 0.0f);
    glRotatef(rot->rotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(rot->rotation.z, 0.0f, 0.0f, 1.0f);

    glTranslatef(- rot->axe.x,
		 - rot->axe.y,
		 - rot->axe.z);

    glColor4f(color->r, color->g, color->b, color->a);
    glCallList(sprite->animation->displayList[sprite->index]);

    if ((sprite->timeCounter += time) >= sprite->animation->timeSteps[sprite->index])
      {
	++sprite->index;
	if (sprite->index >= sprite->animation->stepNumber)
	  sprite->index = 0;
	sprite->timeCounter = 0.0f;
      }

    glPopMatrix();
    (void)color;
    (void)rot;
    (void)ev;
  }

private:
};

#endif				// __SPRITE_SYSTEM_HPP__
