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
    require<Shader>();
    // require<Rotation>();
    // require<Scale>();
    // require<Color>();
  }

  virtual void			update(EntityData &entity, float, const ALLEGRO_EVENT &ev)
  {
    Model			*model = ComponentManager::getInstance().getComponent<Model>(entity);
    Position			*pos = ComponentManager::getInstance().getComponent<Position>(entity);
    Shader			*shader = ComponentManager::getInstance().getComponent<Shader>(entity);
    glPushMatrix();
    
    glTranslatef(pos->position.x, pos->position.y, pos->position.z);

    // enable shader
    glUseProgram(shader->getProgram()->getId());

    glBindTexture(GL_TEXTURE_2D, shader->getFirstTexture()->getImage()->getTexture());

    glBindBuffer(GL_ARRAY_BUFFER, model->obj->getVertexBuffer());    
    glVertexPointer(3, GL_FLOAT, 0, (void*)(0));
    glBindBuffer(GL_ARRAY_BUFFER, shader->getFirstTexture()->getBufferId());
    glTexCoordPointer(2, GL_FLOAT, 0, (void*)(0));

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glDrawArrays(GL_TRIANGLES, 0, model->obj->getVerticesNumber());

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    

    // // apply vertex buffer
    // glBindBuffer(GL_ARRAY_BUFFER, model->obj->getVertexBuffer());
    // glVertexAttribPointer(0,                  // attribute
    // 			  3,                  // size
    // 			  GL_FLOAT,           // type
    // 			  GL_FALSE,           // normalized?
    // 			  0,                  // stride
    // 			  (void*)0            // array buffer offset
    // 			  );
    // glEnableVertexAttribArray(0);

    // // bind textures buffers
    // shader->bindTexturesBuffers();

    // // unbind buffers
    // glBindBuffer(GL_ARRAY_BUFFER, 0);

    // // bind textures
    // shader->bindTextures();
    // glEnableClientState (GL_VERTEX_ARRAY);
    // glEnableClientState (GL_ELEMENT_ARRAY_BUFFER);
    // glDrawArrays(GL_TRIANGLES, 0, model->obj->getVerticesNumber());
    // glDisableClientState (GL_VERTEX_ARRAY);
    // glDisableClientState (GL_ELEMENT_ARRAY_BUFFER);
    
    // // shader->drawTexturesBuffers();

    // glBindTexture(GL_TEXTURE_2D, 0);
    // glDisableVertexAttribArray(0);
    // glDisableVertexAttribArray(1);

    // disable shader
    glUseProgram(0);
    glPopMatrix();

    (void)ev;
  }

private:
};

#endif				// __OBJ_MODEL_SYSTEM_HPP__
