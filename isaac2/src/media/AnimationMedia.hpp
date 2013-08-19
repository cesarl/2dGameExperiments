#ifndef					__ANIMATION_MEDIA_HH__
# define				__ANIMATION_MEDIA_HH__

#include	                        <glm/glm.hpp>
#include				"ImageMedia.hpp"
#include				"Resource.hh"
#include				"SmartPointer.hpp"
#include				"SmartPointerPolicies.hpp"


class					AnimationMedia : public Resource
{
public:
  struct				Coords
  {
    glm::vec2				pos;
    glm::vec2				dim;
  };

public:
  ImageMediaPtr				img;
  double				*timeSteps;
  unsigned int				stepNumber;
  bool					reverse;
  int					cycleNumber;
  Coords				*coordinates;
  GLuint				*displayList;

public:
  AnimationMedia(ImageMediaPtr img_,
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
    displayList = new GLuint[stepNumber]();

    if (!displayList)
      {
	// todo throw error no memory
      }
    for (unsigned int i = 0; i < stepNumber; ++i)
      {
	displayList[i] = glGenLists(1);
	glNewList(displayList[i], GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D, getTexture());

	glBegin(GL_QUADS);

	glTexCoord2f(coordinates[i].pos.x, coordinates[i].pos.y); // Top left hand corner
	glVertex3f(0.0, 0.0, 0.0); // X,Y,Z
	glTexCoord2f(coordinates[i].dim.x, coordinates[i].pos.y); // Bottom left hand corner
	glVertex3f(1.0, 0.0, 0.0); // X,Y,Z
	glTexCoord2f(coordinates[i].dim.x, coordinates[i].dim.y); // Bottom right hand corner
	glVertex3f(1.0, 1.0, 0.0); // X,Y,Z
	glTexCoord2f(coordinates[i].pos.x, coordinates[i].dim.y); // Top right hand corner
	glVertex3f(0.0, 1.0, 0.0); // X,Y,Z
	glEnd();
	glEndList(); 
      }
  }

  virtual void				operator=(AnimationMedia & o)
  {
    img = o.img;
    timeSteps = o.timeSteps;
    stepNumber = o.stepNumber;
    reverse = o.reverse;
    cycleNumber = o.cycleNumber;
    coordinates = o.coordinates;
    displayList = o.displayList;
  }

  virtual ~AnimationMedia()
  {
  }

  inline GLuint				getTexture()
  {
    return img->getTexture();
  }

};

typedef					SmartPtr<AnimationMedia, InternalRef> AnimationMediaPtr;

#endif					// __ANIMATION_MEDIA_HH__
