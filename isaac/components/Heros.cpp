#include				"Heros.hh"
#include				"ComponentTypes.hh"

#include				<iostream> //pour le debug - a virer

Heros::Heros(Entity *entity) : AComponent(entity, T_HEROS, 1)
{
  SPRITE(entity);
  MOVE(entity);
  MOVE(entity)->setFriction(0.04, 0.04);
  INPUT(entity)->listen(true);
  BOUNDING_BOX(entity)->setWidth(64);
  BOUNDING_BOX(entity)->setHeight(64);
}

Heros::~Heros()
{}

void					Heros::update(double time)
{
  if (this->updateTimestamp == time)
    return;
  this->updateTimestamp = time;

  Input					*input;
  Move					*move;

  input = INPUT(this->entity);
  move = MOVE(this->entity);

  if (input->up)
    {
      move->setDirectionY(-4);
    }
  if (input->down)
    {
      move->setDirectionY(4);
    }
  if (input->left)
    {
      move->setDirectionX(-4);
    }
  if (input->right)
    {
      move->setDirectionX(4);
    }
}

void					Heros::draw()
{}
