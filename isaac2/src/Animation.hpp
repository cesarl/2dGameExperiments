#ifndef					__ANIMATION_HH__
# define				__ANIMATION_HH__

#include	                        <glm/glm.hpp>
#include				"Image.hpp"
#include				"Resource.hh"
#include				"SmartPointer.hpp"
#include				"SmartPointerPolicies.hpp"


class					Animation : public Resource
{
public:
  struct				Coords
  {
    glm::vec2				pos;
    glm::vec2				dim;
  };

public:
  ImagePtr				img;
  double				*timeSteps;
  unsigned int				stepNumber;
  bool					reverse;
  int					cycleNumber;
  Coords				*coordinates;

public:
  Animation(ImagePtr img_,
	    double *timeSteps_,
	    unsigned int stepNumber_,
	    bool reverse_,
	    int cycleNumber_,
	    Coords * coordinates_,
	    const std::string & name,
	    bool force) :
    Resource(name, force),
    img(img_),
    timeSteps(timeSteps_),
    stepNumber(stepNumber_),
    reverse(reverse_),
    cycleNumber(cycleNumber_),
    coordinates(coordinates_)
  {
    
  }

  virtual void				operator=(Animation & o)
  {
    img = o.img;
    timeSteps = o.timeSteps;
    stepNumber = o.stepNumber;
    reverse = o.reverse;
    cycleNumber = o.cycleNumber;
    coordinates = o.coordinates;
  }

  virtual ~Animation()
  {
  }

  GLuint				getTexture()
  {
    return img->getTexture();
  }

  unsigned int				getStepNumber() const
  {
    return stepNumber;
  }

  void					draw(unsigned int index)
  {
    glBindTexture(GL_TEXTURE_2D, getTexture());

    glBegin(GL_QUADS);

    glTexCoord2f(coordinates[index].pos.x, coordinates[index].pos.y); // Top left hand corner
    glVertex3f(0.0, 0.0, 0.0); // X,Y,Z
    glTexCoord2f(coordinates[index].dim.x, coordinates[index].pos.y); // Bottom left hand corner
    glVertex3f(1.0, 0.0, 0.0); // X,Y,Z
    glTexCoord2f(coordinates[index].dim.x, coordinates[index].dim.y); // Bottom right hand corner
    glVertex3f(1.0, 1.0, 0.0); // X,Y,Z
    glTexCoord2f(coordinates[index].pos.x, coordinates[index].dim.y); // Top right hand corner
    glVertex3f(0.0, 1.0, 0.0); // X,Y,Z
    glEnd();
  }

};

typedef					SmartPtr<Animation, InternalRef> AnimationPtr;

#endif					// __ANIMATION_HH__
