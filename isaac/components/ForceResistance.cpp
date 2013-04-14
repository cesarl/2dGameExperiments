#include				"ForceResistance.hh"
#include				"ComponentTypes.hh"

#include				<iostream> //pour le debug - a virer


ForceResistance::ForceResistance(Entity *entity) : AComponent(entity, T_FORCE_RESISTANCE)
{
  MOVE(entity);
  this->resistance_ = 0;
}

ForceResistance::~ForceResistance()
{}

void					ForceResistance::update(double time)
{
  if (this->updateTimestamp == time)
    return;
  this->updateTimestamp = time;
}

void					ForceResistance::draw()
{}

double					ForceResistance::getResistance() const
{
  return this->resistance_;
}

void					ForceResistance::setResistance(double resistance)
{
  this->resistance_ = resistance;
}

void					ForceResistance::applyForce(Entity *o)
{
  Move					*move1;
  Move					*move2;
  double				force1;
  double				force2;
  Position				*pos1;
  Position				*pos2;

  move1 = MOVE(this->entity);
  move2 = MOVE(o);
  force1 = this->resistance_;
  force2 = FORCE_RESISTANCE(o)->getResistance();
  pos1 = POSITION(this->entity);
  pos2 = POSITION(o);


  if (force1 < 0 || force2 < 0)
    {
      if (force1 < 0)
	move2->reverseOneAxe(abs(pos2->x - pos1->x), abs(pos2->y - pos1->y), 0.3);
      else
	move1->reverseOneAxe(abs(pos2->x - pos1->x), abs(pos2->y - pos1->y), 0.3);
      return;
    }

  double				dx;
  double				dy;
  double				angle;
  double				dir1;
  double				dir2;
  double				sp1;
  double				sp2;
  double				vx1;
  double				vx2;
  double				vy1;
  double				vy2;
  double				fvx1;
  double				fvx2;
  double				fvy1;
  double				fvy2;
  double				nvx1;
  double				nvx2;
  double				nvy1;
  double				nvy2;

  dx = pos1->x - pos2->x;
  dy = pos1->y - pos2->y;
  angle = atan2(dy, dx) / M_PI * 180;
  dir1 = move1->getDirection();
  dir2 = move2->getDirection();
  sp1 = sqrt(move1->getDirectionX() * move1->getDirectionX() + move1->getDirectionY() * move1->getDirectionY());
  sp1 = isnan(sp1) ? 0 : sp1;
  sp2 = sqrt(move2->getDirectionX() * move2->getDirectionX() + move2->getDirectionY() * move2->getDirectionY());
  sp2 = isnan(sp2) ? 0 : sp2;
  vx1 = sp1 * cos(dir1 - angle);
  vx1 = isnan(vx1) ? 0 : vx1;
  vy1 = sp1 * sin(dir1 - angle);
  vy1 = isnan(vy1) ? 0 : vy1;
  vx2 = sp2 * cos(dir2 - angle);
  vx2 = isnan(vx2) ? 0 : vx2;
  vy2 = sp2 * sin(dir2 - angle);
  vy2 = isnan(vy2) ? 0 : vy2;
  fvx1 = ((force1 - force2) * vx1 + (force2 + force2) * vx2) / (force1 + force2);
  fvx2 = ((force1 + force1) * vx1 + (force2 - force1) * vx2) / (force1 + force2);
  fvy1 = vy1;
  fvy2 = vy2;
  nvx1 = cos(angle) * fvx1 + cos(angle + M_PI / 2) * fvy1;
  nvx1 = isnan(nvx1) ? 0 : nvx1;
  nvy1 = sin(angle) * fvx1 + sin(angle + M_PI / 2) * fvy1;
  nvy1 = isnan(nvy1) ? 0 : nvy1;
  nvx2 = cos(angle) * fvx2 + cos(angle + M_PI / 2) * fvy2;
  nvx2 = isnan(nvx2) ? 0 : nvx2;
  nvy2 = sin(angle) * fvx2 + sin(angle + M_PI / 2) * fvy2;
  nvy2 = isnan(nvy2) ? 0 : nvy2;
  move1->setDirection(nvx1, nvy1);
  move2->setDirection(nvx2, nvy2);
  // move1->vx = nvx1;
  // move1->vy = nvy1;
  // move2->vx = nvx2;
  // move2->vy = nvy2;
  // move1->vx = move1->vx + move2->vx / force2;
  // move1->vy = move1->vy + move2->vy / force2;
  // move2->vx = move2->vx + move1->vx / force1;
  // move2->vy = move2->vy + move1->vy / force1;
}
