#include				"Move.hh"

#include				<iostream> //pour le debug - a virer

using namespace				ComponentType;


DataMove::DataMove(int typeId, AComponent *component) :
  DataComponent(typeId, component)
{}

Move::Move() : AComponent()
{
}

Move::~Move()
{}

Move				*Move::getInstance()
{
  static Move			that;
  return &that;
}

void					Move::init(Entity *entity)
{
  DataMove				*move;

  POSITION(entity);
  move = entity->getComponent<DataMove>(MOVE()->getTypeId());
  move->vx = 3;
  move->vy = 3;
  move->frictionX = 0.02;
  move->frictionY = 0.02;
  move->gravityX = 0;
  move->gravityY = 0;
}

void					Move::update(Entity *entity, double time)
{
  DataPosition				*position;
  DataMove				*move;

  move = entity->getComponent<DataMove>(MOVE()->getTypeId());

  if (move->updateTimestamp == time)
    return;
  move->updateTimestamp = time;
  position = entity->getComponent<DataPosition>(POSITION()->getTypeId());
  move->vx -= move->frictionX;
  move->vy -= move->frictionY;
  move->vx += move->gravityX;
  move->vy += move->gravityY;
  position->x += move->vx;
  position->y += move->vy;
  (void)entity;
  (void)time;
}

Move				*Move::operator()(Entity *entity)
{
  DataMove			*data;

  if (!entity->getComponent(MOVE()->getTypeId()))
    {
      data = new DataMove(MOVE()->getTypeId(), this);
      entity->addComponent(data);
      this->init(entity);
    }
  return this;
}

Move				*Move::operator()()
{
  return this;
}
