#include				"AContentComponent.hh"

AContentComponent::AContentComponent(unsigned int priority) :
  priority_(priority),
  type_(ABSTRACT_TYPE)
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
