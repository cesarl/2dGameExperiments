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

  void				bindTextures()
  {
    std::map<std::string, TextureMediaPtr>::iterator it;
    unsigned int i = 0;

    it = textures_.begin();
    while (it != textures_.end())
      {
	if (!it->second.hasDataSet())
	  {
	    ++it;
	    continue;
	  }
	glUniform1i(program_->getVarId(it->first), i);
	++it;
	++i;
      }

    it = textures_.begin();
    i = 0;
    while (it != textures_.end())
      {
	if (!it->second.hasDataSet())
	  {
	    ++it;
	    continue;
	  }
	// glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0 + i);
	glBindTexture(GL_TEXTURE_2D, it->second->getImage()->getTexture());
	// glDisable(GL_TEXTURE_2D);
	glUniform1f(program_->getVarId(it->first + "Set"), true);
	++it;
	++i;
      }
    glActiveTexture(GL_TEXTURE0);
  }

  void				applyTexturesCoordinates()
  {
    std::map<std::string, TextureMediaPtr>::iterator it;

    it = textures_.begin();
    while (it != textures_.end())
      {
	if (!it->second.hasDataSet())
	  {
	    ++it;
	    continue;
	  }
	glBindBuffer(GL_ARRAY_BUFFER, it->second->getBufferId());
	glTexCoordPointer(2, GL_FLOAT, 0, (void*)(0));
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

