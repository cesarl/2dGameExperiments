#ifndef					__SHADER_PROGRAM_LOADER_HH__
# define				__SHADER_PROGRAM_LOADER_HH__

#include				<iostream>
#include				<fstream>
#include				<string>
#include				<vector>
#include				<allegro5/allegro.h>
#include				<allegro5/allegro_opengl.h>
#include				"Loader.hpp"
#include				"Shader.hpp"
#include				"ShaderProgram.hpp"

class					ShaderProgramLoader : public Loader<ShaderProgram>
{
public:
  ShaderProgramLoader() : Loader<ShaderProgram>()
  {}

  virtual ~ShaderProgramLoader()
  {}

  virtual ShaderProgram			*load(const File &file, bool force = false)
  {
    GLuint				id;
    std::string				line;
    std::ifstream			myfile(file.getFullName().c_str());
    std::vector<std::string>		list;
    ShaderPtr shader;
ShaderProgram				*program;
    GLint				linkStatus = GL_TRUE;

    if (!myfile.is_open())
      {
	throw LoadingFailed(file.getFullName(), "AnimationLoader failed to load animation.");
      }

    id = glCreateProgram();
    if (id == 0)
      throw LoadingFailed(file.getFullName(), "ShaderProgramLoader failed to create shader.");

    program = new ShaderProgram(id, file.getFileName(), force);

    while (myfile.good())
      {
	std::getline(myfile, line);
	split(line, list, " ");
	if (list.size() != 2)
	  continue;
	if (list[0] == "VERTEX" || list[0] == "PIXEL")
	  {
	    shader = ResourceManager::getInstance().get<Shader>(list[1]);
	    glAttachShader(id, shader->getId());
	    program->add(shader->getId());
	  }
      }    

    glLinkProgram(id);

    if (linkStatus != GL_TRUE)
      {
	GLint				l;
	glGetProgramiv(id, GL_INFO_LOG_LENGTH, &l);
	std::string log(l + 1, '\0');
	glGetProgramInfoLog(id, l, &l, &log[0]);
	std::cout << std::endl << log;
	throw LoadingFailed(file.getFullName(), "ShaderProgramLoader failed to link program.\n");
      }


return program;
  }
  virtual void				save(const ShaderProgram *, const std::string &name)
  {
    throw LoadingFailed(name, "ShaderProgramLoader doesn't support SAVE.");
  }
};

#endif					// __SHADER_PROGRAM_LOADER_HH__
