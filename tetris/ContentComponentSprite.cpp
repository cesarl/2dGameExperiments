#include				"ContentComponentSprite.hh"

ContentComponentSprite::ContentComponentSprite(std::string const & imagePath,
					       int columnNumber,
					       int partWidth,
					       int partHeight,
					       int from,
					       int stepNumber,
					       int currentStep,
					       int speed) :
  ContentComponentImage(imagePath),
  columnNumber_(columnNumber),
  partWidth_(partWidth),
  partHeight_(partHeight),
  from_(from),
  stepNumber_(stepNumber),
  currentStep_(currentStep),
  speed_(speed),
  timeCounter_(-1)
{
  this->type_ = SPRITE_TYPE;
}

ContentComponentSprite::ContentComponentSprite(ALLEGRO_BITMAP *image,
					       int columnNumber,
					       int partWidth,
					       int partHeight,
					       int from,
					       int stepNumber,
					       int currentStep,
					       int speed) :
  ContentComponentImage(image),
  columnNumber_(columnNumber),
  partWidth_(partWidth),
  partHeight_(partHeight),
  from_(from),
  stepNumber_(stepNumber),
  currentStep_(currentStep),
  speed_(speed),
  timeCounter_(-1)
{
  this->type_ = SPRITE_TYPE;
}

ContentComponentSprite::ContentComponentSprite() :
  ContentComponentImage(NULL),
  columnNumber_(1),
  partWidth_(24),
  partHeight_(24),
  from_(0),
  stepNumber_(0),
  currentStep_(0),
  speed_(0),
  timeCounter_(-1)
{
  this->type_ = SPRITE_TYPE;
}

ContentComponentSprite::~ContentComponentSprite()
{}

void					ContentComponentSprite::update(Entity *entity, ALLEGRO_EVENT *event)
{
  if (this->timeCounter_ == -1)
    this->timeCounter_ = al_get_time();
  if (al_get_time() - this->timeCounter_ < this->speed_ || this->stepNumber_ == 0)
    return;
  ++this->currentStep_;
  if (this->currentStep_ > this->stepNumber_ + this->from_)
    this->currentStep_ = this->from_;
  (void)(entity);
  (void)(event);
}

void					ContentComponentSprite::draw(Entity *entity)
{
  if (this->bitmap_)
    al_draw_bitmap_region(this->bitmap_,
			       (this->currentStep_ % this->columnNumber_) * this->partWidth_,
			       (this->currentStep_ / this->columnNumber_) * this->partHeight_,
			       this->partWidth_,
			       this->partHeight_,
			       entity->getX(),
			       entity->getY(),
			       0);
  else
    std::cerr << "Error : ContentComponentSprite - Draw() - Bitmap isn't set" << std::endl;
}


void					ContentComponentSprite::setColumnNumber(int columnNumber)
{
  this->columnNumber_ = columnNumber;
}

void					ContentComponentSprite::setPartWidth(int partWidth)
{
  this->partWidth_ = partWidth;
}

void					ContentComponentSprite::setPartHeight(int partHeight)
{
  this->partHeight_ = partHeight;
}

void					ContentComponentSprite::setFrom(unsigned int from)
{
  this->from_ = from;
}

void					ContentComponentSprite::setStepNumber(unsigned int stepNumber)
{
  this->stepNumber_ = stepNumber;
}

void					ContentComponentSprite::setCurrentStep(unsigned int currentStep)
{
  this->currentStep_ = currentStep;
}

void					ContentComponentSprite::setSpeed(double speed)
{
  this->speed_ = speed;
}
