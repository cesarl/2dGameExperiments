#include			"AComponent.hh"

AComponent::AComponent(int type) : type_(type)
{
  std::cout << "A component of type " << type << " has been created" << std::endl;
}

AComponent::~AComponent()
{}

int				AComponent::getType() const
{
  return this->type_;
}

void				AComponent::setEntity(Entity *entity)
{
  this->entity_ = entity;
}

void				AComponent::subscribe(std::string const & message)
{
  Pubsub::getInstance()->subscribe(this, message);
}

void				AComponent::receiveSubscription(std::string const & message)
{
  std::cout << "Gling ! nouveau message pour un AComponent - le message dit " << message << std::endl;
  (void)message;
  return;
}
