#ifndef					__CONTENT_COMPONENT_SPRITE_HH__
# define				__CONTENT_COMPONENT_SPRITE_HH__

#include				"ContentComponentImage.hh"

class					ContentComponentSprite : public ContentComponentImage
{
public:
  ContentComponentSprite(std::string const & imagePath,
			 int columnNumber = 1,
			 int partWidth = 24,
			 int partHeight = 24,
			 int from = 0,
			 int stepNumber = 0,
			 int currentStep = 0,
			 int speed = 0);
  ContentComponentSprite(ALLEGRO_BITMAP *image,
			 int columnNumber = 1,
			 int partWidth = 24,
			 int partHeight = 24,
			 int from = 0,
			 int stepNumber = 0,
			 int currentStep = 0,
			 int speed = 0);
  ContentComponentSprite();
  ~ContentComponentSprite();
  virtual void				update(Entity *entity, ALLEGRO_EVENT *event);
  virtual void				draw(Entity *entity);
  void					setColumnNumber(int columnNumber);
  void					setPartWidth(int partWidth);
  void					setPartHeight(int partHeight);
  void					setFrom(unsigned int from);
  void					setStepNumber(unsigned int stepNumber);
  void					setCurrentStep(unsigned int currentStep);
  void					setSpeed(double speed);
private:
  int					columnNumber_;
  int					partWidth_;
  int					partHeight_;
  unsigned int				from_;
  unsigned int				stepNumber_;
  unsigned int				currentStep_;
  double				speed_;
  double				timeCounter_;
};

#endif					// __CONTENT_COMPONENT_SPRITE_HH__
