#include				"Entity.hh"
#include				"AComponent.hh"
#include				"Pubsub.hh"

class					PositionComponent : public AComponent
{
public:
  PositionComponent(int x, int y) :
    AComponent(1),
    x_(x),
    y_(y)
  {}
  virtual ~PositionComponent()
  {}
  virtual void				update()
  {
    std::cout << "I'm a position component  of " << this->entity_->getName() << " and my location is x : " << this->x_ << " y : " << this->y_ << std::endl;
  }
  void					move(int x, int y)
  {
    this->x_ = x;
    this->y_ = y;
  }
  void					receiveSubscription(std::string const & message)
  {
    std::cout << "j ai recu un message" << std::endl;
    if (message == "avance")
      this->move(20, 30);
  }
private:
  int					x_;
  int					y_;
};

int					main()
{
  Entity				entity("myEntity");
  PositionComponent			positionComponent(0, 0);
  AComponent				*component;

  entity.addComponent(&positionComponent);
  entity.update();

  component = entity.getComponent(1);
  component->subscribe("avance");
  Pubsub::getInstance()->publish("avance");

  entity.update();
  return 0;
}
