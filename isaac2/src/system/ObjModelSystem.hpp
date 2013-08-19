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

    // apply vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, model->obj->getVertexBuffer());
    glVertexAttribPointer(0,                  // attribute
			  3,                  // size
			  GL_FLOAT,           // type
			  GL_FALSE,           // normalized?
			  0,                  // stride
			  (void*)0            // array buffer offset
			  );
    glEnableVertexAttribArray(0);

    // bind textures buffers
    shader->bindTexturesBuffers();

    // unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // pass textures to shaders
    shader->bindTextures();
    // texLoc = glGetUniformLocation(ShaderID, "BaseMap");
    // glUniform1i(texLoc, 0);

    // texLoc = glGetUniformLocation(ShaderID, "ReflectMap");
    // glUniform1i(texLoc, 1);

    // texLoc = glGetUniformLocation(ShaderID, "RefractMap");
    // glUniform1i(texLoc, 2);


    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, Base);

    // glActiveTexture(GL_TEXTURE1);
    // glBindTexture(GL_TEXTURE_2D, Reflection);

    // glActiveTexture(GL_TEXTURE2);
    // glBindTexture(GL_TEXTURE_2D, Refraction);


    // glBindTexture(GL_TEXTURE_2D, texture->texture->getImage()->getTexture());

    glDrawArrays(GL_TRIANGLES, 0, model->obj->getVerticesNumber());
    shader->drawTexturesBuffers();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    // disable shader
    glUseProgram(0);
    glPopMatrix();

    (void)ev;
  }

private:
};

#endif				// __OBJ_MODEL_SYSTEM_HPP__
