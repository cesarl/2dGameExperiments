#include				"Move.hh"

#include				<iostream> //pour le debug - a virer

using namespace				ComponentType;

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

void					Move::update(Entity *entity)
{
  DataPosition				*position;
  DataMove				*move;

  move = entity->getComponent<DataMove>(MOVE()->getTypeId());
  position = entity->getComponent<DataPosition>(POSITION()->getTypeId());
  move->vx -= move->frictionX;
  move->vy -= move->frictionY;
  move->vx += move->gravityX;
  move->vy += move->gravityY;
  position->x += move->vx;
  position->y += move->vy;
(void)entity;
}

Move				*Move::operator()(Entity *entity)
{
  DataMove				*data = new DataMove;

  if (!entity->getComponent(MOVE()->getTypeId()))
    {
      data->component = this;
      data->typeId = MOVE()->getTypeId();
      entity->addComponent(data);
      this->init(entity);
    }
  return this;
}

Move				*Move::operator()()
{
  return this;
}
