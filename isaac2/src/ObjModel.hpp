#ifndef					__OBJ_MODEL_HH__
# define				__OBJ_MODEL_HH__

#include				<allegro5/allegro.h>
#include				<allegro5/allegro_opengl.h>
#include				<GL/glu.h>
#include				<glm/glm.hpp>
#include				"Resource.hh"
#include				"SmartPointer.hpp"
#include				"SmartPointerPolicies.hpp"
#include				"Vector3d.hh"

class					ObjModel : public Resource
{
public:
  ObjModel(GLuint vertices,
	   GLuint uvs,
	   unsigned int verticesNumber,
	   std::string const & name, bool force) :
    Resource(name, force),
    vertices_(vertices),
    uvs_(uvs),
    verticesNumber_(verticesNumber)
  {
  }

  virtual void				operator=(ObjModel & o)
  {
    vertices_ = o.vertices_;
    uvs_ = o.uvs_;
    verticesNumber_ = o.verticesNumber_;
  }

  virtual ~ObjModel()
  {
    glDeleteBuffers(1, &vertices_);
    glDeleteBuffers(1, &uvs_);
  }

  unsigned int				getVerticesNumber() const
  {
    return verticesNumber_;
  }

  GLuint				getVertexBuffer() const
  {
    return vertices_;
  }

  GLuint				getUvBuffer() const
  {
    return uvs_;
  }
private:
  GLuint			vertices_;
  GLuint			uvs_;
  unsigned int			verticesNumber_;
};

typedef					SmartPtr<ObjModel, InternalRef> ObjModelPtr;

#endif					// __OBJ_MODEL_HH__
