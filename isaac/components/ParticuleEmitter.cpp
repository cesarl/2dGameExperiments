#include				"ParticuleEmitter.hh"
#include				"ComponentTypes.hh"

#include				<iostream> //pour le debug - a virer

ParticuleEmitter::ParticuleEmitter(Entity *entity) : AComponent(entity, T_PARTICULE_EMITTER, 1, 2)
{
  POSITION(entity);
  this->width_ = 0;
  this->height_ = 0;
  this->flow_ = 0;
}

ParticuleEmitter::~ParticuleEmitter()
{
  t_iter				it;

  if (!this->list_.empty())
    {
      it = this->list_.begin();
      while (it != this->list_.end())
	{
	  delete (*it);
	  ++it;
	}
    }
}

void					ParticuleEmitter::update(double time)
{
  t_iter				it;
  int					count;
  double				f;

  if (this->updateTimestamp == time)
    return;
  this->updateTimestamp = time;

  it = this->list_.begin();
  count = 0;
  while (it != this->list_.end())
    {
      if (VISIBILITY(*it)->visible)
	{
	  (*it)->update();
	}
      else if (count < this->flow_ / 10)
	{
	  POSITION(*it)->setPos(POSITION(this->entity)->x + rand() % this->width_,
				POSITION(this->entity)->y + rand() % this->height_);
	  VISIBILITY(*it)->setVisible(true);
	  VISIBILITY(*it)->opacity = 255;
	  VISIBILITY(*it)->fadeOut(0.05, 10);
	  ROTATION_FORCE(*it)->launch((float)rand()/RAND_MAX/2 - 0.5, 0.005);
	  f = (double)rand() / RAND_MAX;
	  MOVE(*it)->vx = -3 + f * (3 - -3); // rand() % 6 - 3;
	  MOVE(*it)->vy = (float)rand() / RAND_MAX / 3.0 - 3; // rand() % 6 - 3;
	  ++count;
	}
      ++it;
    }
  // std::cout << this->list_.size() << std::endl;
}

void					ParticuleEmitter::draw()
{
  t_iter				it;

  it = this->list_.begin();
  while (it != this->list_.end())
    {
      if (VISIBILITY(*it)->visible)
	(*it)->draw();
      ++it;
    }
}

void					ParticuleEmitter::config(std::string imagePath,
								 int columnNumber,
								 int partWidth,
								 int partHeight,
								 unsigned int possibleFrom,
								 unsigned int stepNumber,
								 double speed,
								 int flow,
								 int width,
								 int height)
{
  t_iter				it;
  int					i;
  Entity				*entity;
  int					step;
  double				f;

  this->flow_ = flow;
  this->width_ = width;
  this->height_ = height;

  if (!this->list_.empty())
    {
      it = this->list_.begin();
      while (it != this->list_.end())
	{
	  delete (*it);
	  ++it;
	}
    }
  i = 0;
  while (i < flow * 10)
    {
      entity = new Entity();
      step = rand() % possibleFrom * stepNumber;
      SPRITE(entity)->config(columnNumber,
			     partWidth,
			     partHeight,
			     step,
			     stepNumber,
			     step,
			     speed);
      IMAGE(entity)->setBitmap(imagePath);
      ROTATION(entity);
      ROTATION_FORCE(entity)->launch((float)rand()/RAND_MAX/2 - 0.5, 0.005);
      f = (double)rand() / RAND_MAX;
      MOVE(entity)->vx = -3 + f * (3 - -3); // rand() % 6 - 3;
      MOVE(entity)->vy = (float)rand() / RAND_MAX / 3 - 1.5; // rand() % 6 - 3;
      MOVE(entity)->gravityY = 0.1;
      VISIBILITY(entity)->setVisible(false);
      this->list_.push_back(entity);
      ++i;
    }
}

void					ParticuleEmitter::setWidth(int width)
{
  this->width_ = width;
}

void					ParticuleEmitter::setHeight(int height)
{
  this->height_ = height;
}

// void					ParticuleEmitter::play(double time)
// {
//   this->time
// }


void					ParticuleEmitter::serialize(std::ofstream *file)
{
  int					type = T_PARTICULE_EMITTER;

  file->write(reinterpret_cast<const char *>(&type), sizeof(type));
  file->write(reinterpret_cast<const char *>(&this->width_), sizeof(int));
  file->write(reinterpret_cast<const char *>(&this->height_), sizeof(int));
  file->write(reinterpret_cast<const char *>(&this->flow_), sizeof(int));
}

void					ParticuleEmitter::unserialize(std::ifstream *file)
{
  file->read(reinterpret_cast<char *>(&this->width_), sizeof(int));
  file->read(reinterpret_cast<char *>(&this->height_), sizeof(int));
  file->read(reinterpret_cast<char *>(&this->flow_), sizeof(int));
}
