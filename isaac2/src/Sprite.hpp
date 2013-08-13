#ifndef					__ANIMATION_HH__
# define				__ANIMATION_HH__

#include	                        <glm/glm.hpp>
#imclude				"Img.hpp"

class					Animation : public Resource
{

  struct				Coords
  {
    glm::vec2				pos;
    glm::vec2				dim;
  }

private:
  ImagePtr				img_;
  double				*timeSteps_;
  unsigned int				stepNumber_;
  bool					reverse_;
  int					cycleNumber_;
  Coords				coordinates_;

public:
  Animation(ImagePtr img,
	    double *timeSteps,
	    unsigned int stepNumber,
	    bool reverse,
	    int cycleNumber,
	    const Coords & coordinates,
	    const std::string & name,
	    bool force) :
    Resource(name, force),
    img_(img),
    timeSteps_(timeSteps_),
    stepNumber_(stepNumber),
    reverse_(reverse),
    cycleNumber_(cycleNumber),
    coordinates_(coordinates)
  {
    
  }
};

#endif					// __ANIMATION_HH__
