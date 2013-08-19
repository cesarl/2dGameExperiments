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
    require<Rotation>();
    require<Scale>();
    require<Color>();
  }

  virtual void			update(EntityData &entity, float, const ALLEGRO_EVENT &ev)
  {
    Model			*model = ComponentManager::getInstance().getComponent<Model>(entity);
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

    glBindBuffer(GL_ARRAY_BUFFER, model->obj->getUvBuffer());
    glVertexAttribPointer(1,                  // attribute
			  2,                  // size
			  GL_FLOAT,           // type
			  GL_FALSE,           // normalized?
			  0,                  // stride
			  (void*)0            // array buffer offset
			  );
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDrawArrays(GL_TRIANGLES, 0, model->obj->getVerticesNumber());
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glPopMatrix();

    (void)color;
    (void)rot;
    (void)ev;
  }

private:
};

#endif				// __OBJ_MODEL_SYSTEM_HPP__
