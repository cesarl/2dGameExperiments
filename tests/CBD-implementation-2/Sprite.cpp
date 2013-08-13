#include				<iostream> // for debug
#include				"Sprite.hh"
#include				"ComponentTypes.hh"

Sprite::Sprite(Entity *entity) : AComponent(entity, T_SPRITE, 1, 2)
{
  POSITION(entity);
  IMAGE(entity);

  this->columnNumber = 0;
  this->partWidth = 0;
  this->partHeight = 0;
  this->from = 0;
  this->stepNumber = 0;
  this->currentStep = 0;
  this->speed = 0;
  this->timeCounter_ = -1;
}

Sprite::~Sprite()
{}

void					Sprite::update(double time)
{
  if (this->timeCounter_ == -1)
    this->timeCounter_ = time;
  if (time - this->timeCounter_ < this->speed || this->stepNumber == 0)
    return;
  ++this->currentStep;
  if (this->currentStep >= this->stepNumber + this->from)
    this->currentStep = this->from;
  this->timeCounter_ = time;
}

void					Sprite::draw()
{
  Position				*position;
  Image					*image;
  unsigned char				opacity = VISIBILITY(this->entity)->opacity;
  float					angle = ROTATION(this->entity)->angle;

  if (!VISIBILITY(this->entity)->visible)
    return;
  position = POSITION(this->entity);
  image = IMAGE(this->entity);
  if (image->bitmap)
    al_draw_tinted_scaled_rotated_bitmap_region(image->bitmap,
						(this->currentStep % this->columnNumber) * this->partWidth,
						(this->currentStep / this->columnNumber) * this->partHeight,
						this->partWidth,
						this->partHeight,
						al_map_rgba(opacity, opacity, opacity, opacity),
						angle == 0 ? 0 : this->partWidth / 2,
						angle == 0 ? 0 : this->partHeight / 2,
						angle == 0 ? position->x : position->x + this->partWidth / 2,
						angle == 0 ? position->y : position->y + this->partHeight / 2,
						1,
						1,
						angle,
						0);
}

void					Sprite::config(int columnNumber,
					       int partWidth,
					       int partHeight,
					       unsigned int from,
					       unsigned int stepNumber,
					       unsigned int currentStep,
					       double speed)
{
  this->columnNumber = columnNumber;
  this->partWidth = partWidth;
  this->partHeight = partHeight;
  this->from = from;
  this->stepNumber = stepNumber;
  this->currentStep = currentStep;
  this->speed = speed;
}
