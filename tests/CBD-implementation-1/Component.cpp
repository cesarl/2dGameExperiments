#include				"Component.hh"

DataComponent::DataComponent(int typeId, AComponent *component) :
  updatePriority(0),
  drawPriority(0),
  entity(NULL),
  component(component),
  entityId(0),
  typeId(typeId),
  updateTimestamp(0)
{}

DataComponent::~DataComponent()
{}
