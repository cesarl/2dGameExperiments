#ifndef				__OBJ_MODEL_SYSTEM_HPP__
# define			__OBJ_MODEL_SYSTEM_HPP__

#include			"System.hpp"
#include			"ComponentManager.hpp"
#include			"Components.hpp"

class				ObjModelSystem : public System
{
public:
  virtual ~ObjModelSystem(){};
  ObjModelSystem() : System()
  {}

  virtual void			init()
  {
    require<Model>();
    require<Position>();
    require<Texture>();
    // require<Rotation>();
    // require<Scale>();
    // require<Color>();
  }

  virtual void			update(EntityData &entity, float, const ALLEGRO_EVENT &ev)
  {
    Model			*model = ComponentManager::getInstance().getComponent<Model>(entity);
    Position			*pos = ComponentManager::getInstance().getComponent<Position>(entity);
    Texture			*texture = ComponentManager::getInstance().getComponent<Texture>(entity);

    glPushMatrix();
    
    glTranslatef(pos->position.x, pos->position.y, pos->position.z);

    // here
    glBindBuffer(GL_ARRAY_BUFFER, model->obj->getVertexBuffer());
    glVertexAttribPointer(0,                  // attribute
			  3,                  // size
			  GL_FLOAT,           // type
			  GL_FALSE,           // normalized?
			  0,                  // stride
			  (void*)0            // array buffer offset
			  );
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, texture->texture->getBufferId());
    glVertexAttribPointer(1,                  // attribute
			  2,                  // size
			  GL_FLOAT,           // type
			  GL_FALSE,           // normalized?
			  0,                  // stride
			  (void*)0            // array buffer offset
			  );
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, texture->texture->getImage()->getTexture());
    glDrawArrays(GL_TRIANGLES, 0, model->obj->getVerticesNumber());
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glPopMatrix();

    (void)ev;
  }

private:
};

#endif				// __OBJ_MODEL_SYSTEM_HPP__
