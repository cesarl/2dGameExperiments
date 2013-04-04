#include				"AContentComponent.hh"

AContentComponent::AContentComponent(e_contentComponentType type) :
  priority_(0),
  type_(type)
{}

AContentComponent::~AContentComponent()
{}

void					AContentComponent::setPriority(unsigned int priority)
{
  this->priority_ = priority;
}

unsigned int				AContentComponent::getPriority() const
{
  return this->priority_;
}

int					AContentComponent::getType() const
{
  return this->type_;
}
