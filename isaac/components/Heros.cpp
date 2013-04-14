#include				"Heros.hh"
#include				"ComponentTypes.hh"

#include				<iostream> //pour le debug - a virer

Heros::Heros(Entity *entity) : AComponent(entity, T_HEROS, 1)
{
  MOVE(entity)->setFriction(0.04, 0.04);
  INPUT(entity)->listen(true);
  BOUNDING_BOX(entity)->setDimension(30, 30);
  BOUNDING_BOX(entity)->setMargin(17, 17);
  SPRITE(entity)->config(8, 64, 64, 8, 8, 8, 0.12);
  IMAGE(entity)->setBitmap("assets/imgs/heros.png");
  FORCE_RESISTANCE(entity)->setResistance(3);
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
