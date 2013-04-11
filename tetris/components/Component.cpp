#include				"Component.hh"

AComponent::AComponent(Entity *entity, int typeId, int updatePriority, int drawPriority) :
  updatePriority(updatePriority),
  drawPriority(drawPriority),
  entity(entity),
  entityId(0),
  typeId(typeId),
  updateTimestamp(0)
{
}

AComponent::~AComponent()
{}

