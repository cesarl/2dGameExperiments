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
	  POSITION(e)->setPos(j * CELL_SIZE, i * CELL_SIZE);
	}
    }
  return true;
}
