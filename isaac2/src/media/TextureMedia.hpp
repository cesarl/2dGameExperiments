#ifndef					__TEXTURE_MEDIA_HH__
# define				__TEXTURE_MEDIA_HH__

#include				<allegro5/allegro.h>
#include				<allegro5/allegro_opengl.h>
#include				<GL/glu.h>
#include				<glm/glm.hpp>
#include				"Resource.hh"
#include				"SmartPointer.hpp"
#include				"SmartPointerPolicies.hpp"
#include				"Vector3d.hh"

class					TextureMedia : public Resource
{
public:
  TextureMedia(GLuint bufferId,
	       unsigned int bufferSize,
	       const ImageMediaPtr & img,
	       std::string const & name, bool force) :
    Resource(name, force),
    bufferId_(bufferId),
    bufferSize_(bufferSize),
    img_(img)
  {
  }

  virtual void				operator=(TextureMedia & o)
  {
    bufferId_ = o.bufferId_;
    img_ = o.img_;
    bufferSize_ = o.bufferSize_;
  }

  virtual ~TextureMedia()
  {
    glDeleteBuffers(1, &bufferId_);
  }

  GLuint				getBufferId() const
  {
    return bufferId_;
  }

  unsigned int				getBufferSize() const
  {
    return bufferSize_;
  }

  ImageMediaPtr				getImage() const
  {
    return img_;
  }
private:
  GLuint			bufferId_;
  unsigned int			bufferSize_;
  ImageMediaPtr			img_;
};

typedef					SmartPtr<TextureMedia, InternalRef> TextureMediaPtr;

#endif					// __TEXTURE_MEDIA_HH__
