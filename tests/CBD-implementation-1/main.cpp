#include				"Entity.hh"
#include				"Component.hh"
#include				"System.hh"
#include				"ComponentTypes.hh"

int					main()
{
  Entity				*entity;

  entity = System::getInstance()->createEntity();
  MOVE(entity);
  entity->update();
  while (POSITION()->getX(entity) < 100)
    entity->update();
  return 0;
}
