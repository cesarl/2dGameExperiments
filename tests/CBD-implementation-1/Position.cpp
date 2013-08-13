#include				"Position.hh"

#include				<iostream> //pour le debug - a virer

using namespace				ComponentType;

DataPosition::DataPosition(int typeId, AComponent *component) :
  DataComponent(typeId, component)
{}


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
  entity->getComponent<DataPosition>(POSITION()->getTypeId())->x = 10;
  entity->getComponent<DataPosition>(POSITION()->getTypeId())->y = 10;
}

void					Position::update(Entity *entity, double time)
{
  DataPosition				*data;
 
  data = entity->getComponent<DataPosition>(POSITION()->getTypeId());
  if (data->updateTimestamp == time)
    return;
  data->updateTimestamp = time;
  std::cout << "x : " << data->x << std::endl;
  (void)time;
}

Position				*Position::operator()(Entity *entity)
{
  DataPosition				*data;

  if (!entity->getComponent(this->typeId_))
    {
      data = new DataPosition(POSITION()->getTypeId(), this);
      entity->addComponent(data);
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
  return entity->getComponent<DataPosition>(POSITION()->getTypeId())->x;
}
