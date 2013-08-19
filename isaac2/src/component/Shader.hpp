#ifndef				__SHADER_COMPONENT_HPP__
# define			__SHADER_COMPONENT_HPP__

#include			"Component.hpp"
#include			"ObjModelMedia.hpp"

struct				Shader : public Component<Shader>
{
  Shader			&operator=(const Shader &o)
  {
    program_ = o.program_;
    textures_ = o.textures_;
    return *this;
  }

  void				setShader(const std::string & name)
  {
    program_ = ResourceManager::getInstance().get<ShaderProgramMedia>(name);

    textures_.clear();
    std::map<std::string, std::string> t = program_->getTextures();
    std::map<std::string, std::string>::iterator it;

    it = t.begin();
    for (; it != t.end(); ++it)
      {
	if (it->second != "null")
	  {
	    textures_.insert(std::pair<std::string, TextureMediaPtr>(it->first,
								     ResourceManager::getInstance().get<TextureMedia>(it->second)
								     ));
	  }
	else
	  {
	    textures_.insert(std::pair<std::string, TextureMediaPtr>(it->first,
								     TextureMediaPtr()
								     ));
	  }
      }
  }

  void				bindTexturesBuffers()
  {
    std::map<std::string, TextureMediaPtr>::iterator it;
    unsigned int i = 1;

    it = textures_.begin();
    while (it != textures_.end())
      {
	glBindBuffer(GL_ARRAY_BUFFER, it->second->getBufferId());
	glTexCoordPointer(    2,                  // size
			      GL_FLOAT,           // type
			      0,                  // stride
			      (void*)0            // array buffer offset
			      );
	glEnableVertexAttribArray(i);
	glUniform1i(program_->getVarId(it->first), i - 1);
	++i;
	++it;
      }
  }

  void				bindTextures()
  {
    std::map<std::string, TextureMediaPtr>::iterator it;
    unsigned int i = 0;

    it = textures_.begin();
    while (it != textures_.end())
      {
	glActiveTexture(GL_TEXTURE0 + i);
	glBindTexture(GL_TEXTURE_2D, it->second->getImage()->getTexture());
	++it;
	++i;
      }
  }

  TextureMediaPtr		&getFirstTexture()
  {
    return textures_.begin()->second;
  }

  TextureMediaPtr		&getSecondTexture()
  {
    std::map<std::string, TextureMediaPtr>::iterator it;
    it = textures_.begin();
    ++it;
    return it->second;
  }

  void				drawTexturesBuffers()
  {
    std::map<std::string, TextureMediaPtr>::iterator it;
    unsigned int i = 1;

    it = textures_.begin();
    while (it != textures_.end())
      {
	glDrawArrays(GL_TRIANGLES, i, it->second->getBufferSize());
	++i;
	++it;
      }
  }

  ShaderProgramMediaPtr		&getProgram()
  {
    return program_;
  }
private:
  ShaderProgramMediaPtr		program_;
  std::map<std::string, TextureMediaPtr> textures_;
};

#endif				// __SHADER_COMPONENT_HPP__

