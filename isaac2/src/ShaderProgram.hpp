#ifndef					__SHADER_PROGRAM_HH__
# define				__SHADER_PROGRAM_HH__

#include				<allegro5/allegro.h>
#include				<allegro5/allegro_opengl.h>
#include				<GL/glu.h>
#include				"Resource.hh"
#include				"SmartPointer.hpp"
#include				"SmartPointerPolicies.hpp"
#include				"Vector3d.hh"

class					ShaderProgram : public Resource
{
public:
  ShaderProgram(GLuint id, std::string const & name, bool force) :
    Resource(name, force),
    id_(id)
  {
    shaders_[0] = 0;
    shaders_[1] = 0;
  }

  virtual void				operator=(ShaderProgram & o)
  {
    (void)o;
  }

  virtual ~ShaderProgram()
  {
    if (id_ != 0)
      glDeleteProgram(id_);
  }

  void					add(GLuint shader)
  {
    if (shaders_[0] != 0)
      {
	if (shaders_[1] == 0)
	  {
	    shaders_[1] = shader;
	  }
      }
    else
      shaders_[0] = shader;
  }

  GLuint				getId() const
  {
    return id_;
  }
private:
  GLuint				id_;
  GLuint				shaders_[2];
};

typedef					SmartPtr<ShaderProgram, InternalRef> ShaderProgramPtr;

#endif					// __SHADER_PROGRAM_HH__
