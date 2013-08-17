#ifndef					__SHADER_HH__
# define				__SHADER_HH__

#include				<allegro5/allegro.h>
#include				<allegro5/allegro_opengl.h>
#include				<GL/glu.h>
#include				"Resource.hh"
#include				"SmartPointer.hpp"
#include				"SmartPointerPolicies.hpp"
#include				"Vector3d.hh"

class					Shader : public Resource
{
public:
  Shader(GLuint id, std::string const & name, bool force) :
    Resource(name, force),
    id_(id)
  {
  }

  virtual void				operator=(Shader & o)
  {
    (void)o;
  }

  virtual ~Shader()
  {
    if (id_ != 0)
      glDeleteShader(id_);
  }

  GLuint				getId() const
  {
    return id_;
  }
private:
  GLuint				id_;
};

typedef					SmartPtr<Shader, InternalRef> ShaderPtr;

#endif					// __SHADER_HH__
