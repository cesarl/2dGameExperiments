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

private:
  ImagePtr				img_;
  double				*timeSteps_;
  unsigned int				stepNumber_;
  bool					reverse_;
  int					cycleNumber_;
  Coords				*coordinates_;

public:
  Animation(ImagePtr img,
	    double *timeSteps,
	    unsigned int stepNumber,
	    bool reverse,
	    int cycleNumber,
	    Coords * coordinates,
	    const std::string & name,
	    bool force) :
    Resource(name, force),
    img_(img),
    timeSteps_(timeSteps),
    stepNumber_(stepNumber),
    reverse_(reverse),
    cycleNumber_(cycleNumber),
    coordinates_(coordinates)
  {
    
  }

  virtual void				operator=(Animation & o)
  {
    img_ = o.img_;
    timeSteps_ = o.timeSteps_;
    stepNumber_ = o.stepNumber_;
    reverse_ = o.reverse_;
    cycleNumber_ = o.cycleNumber_;
    coordinates_ = o.coordinates_;
  }

  virtual ~Animation()
  {
  }

};

typedef					SmartPtr<Animation, InternalRef> AnimationPtr;

#endif					// __ANIMATION_HH__
