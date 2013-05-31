#include			"GenerationRules.hh"


bool				gnRoom(EntityManager *mgr, int seed)
{
  Entity			*e;

  if (seed != -1)
    srand(seed);
  for (int i = 0; i < 10; ++i)
    {
      for (int j = 0; j < 20; ++j)
	{
	  e = mgr->create();
	  if (!e)
	    return false;
	  IMAGE(e)->setBitmap("assets/imgs/decor.png");
	  if (rand() % 6 != 0)
	    {
	      SPRITE(e)->config(4, 64, 64, 9, 0, 9, 0);
	      BOUNDING_BOX(e)->setCollidable(false);
	      *TEXT(e) = "ground";
	    }
	  else
	    {
	      SPRITE(e)->config(4, 64, 64, 4, 0, 4, 0);
	      COLLISION_TYPE(e)->setType(FIX_GO);
	      *TEXT(e) = "wall";
	    }
	  BOUNDING_BOX(e)->setDimension(64, 64);
	  FORCE_RESISTANCE(e)->setResistance(-1);
	  COLLISION_TYPE(e)->setType(FIX_GO);
	  POSITION(e)->setPos(j * CELL_SIZE, i * CELL_SIZE, 1);
	}
    }
  return true;
}

bool				gnPnj(EntityManager *mgr, int seed)
{
  int				nb;
  int				i;
  Entity			*e;

  if (seed)
    srand(seed);
  else
    srand(time(0));
  nb = rand() % 50 + 1;
  i = 0;
  while (i < nb)
    {
      e = mgr->create();
      if (!e)
	return false;
      SPRITE(e)->config(8, 64, 64, 8, 8, 8, 0.12);
      IMAGE(e)->setBitmap("assets/imgs/mummy.png");
      FORCE_RESISTANCE(e)->setResistance(1);
      MOVE(e)->setFriction(0.07, 0.07);
      BOUNDING_BOX(e)->setDimension(30, 30);
      BOUNDING_BOX(e)->setMargin(17, 17);
      DAMAGE(e)->setMagnitude(3);
      DAMAGE(e)->setDamageNb(-1);
      PNJ_HEALTH(e)->setHealth(10);
      DANGER_TYPE(e)->setType(BAD);
      COLLISION_TYPE(e)->setType(ACTOR);
      PNJ_DEATH(e);
      *TEXT(e) = "mommy";
      POSITION(e)->setPos(rand() % 1000, rand() % 600, 2);
      ++i;
    }
  return true;
}

bool				gnHeros(EntityManager *mgr, int)
{
  Entity			*e;

  e = mgr->create();
  if (!e)
    return false;
  HEROS(e);
  MOVE(e)->setMaxSpeed(4);
  POSITION(e)->setPos(64 * 20 / 2 - 32, 64 * 10 / 2 - 32, 2);
  return true;
}

bool				gnTest(EntityManager *mgr, int)
{
  Entity			*e;

  e = mgr->create();
  if (!e)
    return false;
  IMAGE(e)->setBitmap("assets/imgs/mummy.png");
  SPRITE(e)->config(8, 64, 64, 8, 8, 8, 0.12);
  POSITION(e)->setPos(64 * 20 / 2 - 32, 64 * 10 / 2 - 32, 2);
  *TEXT(e) = "moi j'te dis lol";
  return true;
}
