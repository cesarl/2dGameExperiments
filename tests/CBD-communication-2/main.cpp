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
  {
    this->subscribe("avance");
  }
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
  int					getX() const
  {
    return this->x_;
  }
  int					getY() const
  {
    return this->y_;
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

class					DrawComponent : public AComponent
{
public:
  DrawComponent() :
    AComponent(2)
  {
  }
  virtual ~DrawComponent()
  {}
  virtual void				update()
  {
    PositionComponent			*component;

    component = dynamic_cast<PositionComponent*>(this->entity_->getComponent(1));

    std::cout << "Je suis un composant de type Draw et je vais te dire ou se troube mon copain de type Dimension ! : " << std::endl;
    std::cout << "--------------> X : " << component->getX() << "   " << "Y : " << component->getY() << std::endl;

  }
  void					receiveSubscription(std::string const & message)
  {
    (void)message;
  }
private:
  int					x_;
  int					y_;
};

int					main()
{
  Entity				entity("myEntity");
  PositionComponent			positionComponent(0, 0);
  DrawComponent				drawComponent;

  entity.addComponent(&positionComponent);
  entity.addComponent(&drawComponent);
  entity.update();

  Pubsub::getInstance()->publish("avance");

  entity.update();
  return 0;
}
