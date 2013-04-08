#include				"Position.hh"

#include				<iostream> //pour le debug - a virer

using namespace				ComponentType;

Position::Position() : AComponent()
{}

Position::~Position()
{}

Position				*Position::getInstance()
{
  static Position			that;
  return &that;
}

void					Position::init(Entity *entity)
{
  entity->getComponent<DataPosition>(this->typeId_)->x = 10;
  entity->getComponent<DataPosition>(this->typeId_)->y = 10;
}

void					Position::update(Entity *entity)
{
  DataPosition				*data;

  data = entity->getComponent<DataPosition>(this->typeId_);

  ++data->x;
  std::cout << "x : " << data->x << std::endl;
}

Position				*Position::operator()(Entity *entity)
{
  DataPosition				*data = new DataPosition;

  if (!entity->getComponent(this->typeId_))
    {
      entity->addComponent(data);
      data->component = this;
      data->typeId = this->typeId_;
      this->init(entity);
    }
  return this;
}

Position				*Position::operator()()
{
  return this;
}

int					Position::getX(Entity *entity) const
{
  return entity->getComponent<DataPosition>(this->typeId_)->x;
}
