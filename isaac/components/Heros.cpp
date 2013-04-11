#include				"Heros.hh"
#include				"ComponentTypes.hh"

#include				<iostream> //pour le debug - a virer

Heros::Heros(Entity *entity) : AComponent(entity, T_HEROS, 1)
{
  SPRITE(entity);
  MOVE(entity);
  MOVE(entity)->setFriction(0.07, 0.07);
  INPUT(entity)->listen(true);
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
      move->setDirectionY(-2);
    }
  if (input->down)
    {
      move->setDirectionY(2);
    }
  if (input->left)
    {
      move->setDirectionX(-2);
    }
  if (input->right)
    {
      move->setDirectionX(2);
    }
}

void					Heros::draw()
{}
