#include				"System.hh"

System::System()
{}

System::~System()
{}

System					*System::getInstance()
{
  static System				that;
  return &that;
}

Entity					*System::createEntity()
{
  Entity				*entity;

  entity = new Entity;
  entity->setId(IdManager::getInstance()->newId());
  this->entityList_.insert(t_pair_entity(entity->getId(), entity));
  return entity;
}

Entity					*System::getEntity(int id) const
{
  t_const_iter_entitylist		it;

  it = this->entityList_.find(id);
  if (it == this->entityList_.end())
    return 0;
  return it->second;
}

// Component				*System::createComponent(int type)
// {
//   DataComponent				*component;
//   t_iter_unusedComponentlist		it;

//   it = this->unsuedComponentList_.find(type);
//   if (it != this->unsuedComponentList_.end())
//     return it->second;
//   component = new Component();
//   component->type = type;
//   this->unsuedComponentList_.insert(t_pair_component(type, component));
//   return component;
// }

// template				<typename T>
// T					*System::createComponent(int type)
// {
//   T					*component;
//   t_iter_unusedComponentlist		it;

//   it = this->unsuedComponentList_.find(type);
//   if (it != this->unsuedComponentList_.end())
//     return static_cast<T>(it->second);
//   component = new Component();
//   component->type = type;
//   this->unsuedComponentList_.insert(t_pair_component(type, component));
//   return static_cast<T>(component);
// }

// template				<typename T>
// T					*System::getComponent(int entityId, int type) const
// {
//   Entity				*entity;
//   Component				*component;

//   entity = this->getEntity(entityId);
//   return T::entity->getComponent(type);
// }

// template				<typename T>
// T					*System::getComponent(Entity *entityPtr, int type) const
// {
//   return T::entityPtr->getComponent(type);
// }

// template				<typename T>
// T					*System::getComponent(Component *componentBrother, int type) const
// {
//   if (!componentBrother->entity)
//     return 0;
//   return T::componentBrother->entity->getComponent(type);
// }
