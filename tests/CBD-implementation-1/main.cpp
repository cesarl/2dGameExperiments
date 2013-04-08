#include				"Entity.hh"
#include				"Component.hh"
#include				"System.hh"
#include				"Position.hh"
#include				"ComponentTypes.hh"

int					main()
{
  Entity				*entity;

  entity = System::getInstance()->createEntity();
  POSITION(entity);
  POSITION(entity);
  while (POSITION()->getX(entity) < 100000)
    entity->update();
  return 0;
}
