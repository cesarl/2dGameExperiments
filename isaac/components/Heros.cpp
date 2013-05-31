#include				"Heros.hh"
#include				"ComponentTypes.hh"

#include				<iostream> //pour le debug - a virer

Heros::Heros(Entity *entity) : AComponent(entity, T_HEROS, 1, 5)
{
  MOVE(entity)->setFriction(0.08, 0.08);
  INPUT(entity)->listen(true);
  BOUNDING_BOX(entity)->setDimension(30, 30);
  BOUNDING_BOX(entity)->setMargin(17, 17);
  SPRITE(entity)->config(8, 64, 64, 8, 8, 8, 0.12);
  IMAGE(entity)->setBitmap("assets/imgs/heros.png");
  FORCE_RESISTANCE(entity)->setResistance(3);
  PISTOL(entity);
  HEALTH(entity)->setHealth(10);
  COLLISION_TYPE(entity)->setType(ACTOR);
  DANGER_TYPE(entity)->setType(GOOD);
  *TEXT(entity) = "heros";
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
  Pistol				*pistol;

  input = INPUT(this->entity);
  move = MOVE(this->entity);
  pistol = PISTOL(this->entity);

  if (input->up)
    {
      move->incDirectionY(-1);
    }
  if (input->down)
    {
      move->incDirectionY(1);
    }
  if (input->left)
    {
      move->incDirectionX(-1);
    }
  if (input->right)
    {
      move->incDirectionX(1);
    }
  if (input->sup)
    pistol->fire(0, -1);
  if (input->sdown)
    pistol->fire(0, 1);
  if (input->sright)
    pistol->fire(1, 0);
  if (input->sleft)
    pistol->fire(-1, 0);
}

void					Heros::draw()
{
  PISTOL(this->entity)->draw();
  SPRITE(this->entity)->draw();
}
