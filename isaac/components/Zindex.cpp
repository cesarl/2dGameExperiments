#include				"Zindex.hh"
#include				"ComponentTypes.hh"

Zindex::Zindex(Entity *entity) : AComponent(entity, T_POSITION),
				 z_(0)
{}

Zindex::~Zindex()
{}

void					Zindex::update(double time)
{
  if (this->updateTimestamp == time)
    return;
  this->updateTimestamp = time;
}

void					Zindex::draw()
{}

int					Zindex::getIndex() const
{
  return this->z_;
}

void					Zindex::setIndex(int index)
{
  this->z_ = index;
}
