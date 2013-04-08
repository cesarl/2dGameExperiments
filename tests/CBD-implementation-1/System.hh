#ifndef					__SYSTEM_HH__
# define				__SYSTEM_HH__

#include				<list>
#include				<map>
#include				"Entity.hh"

class					Entity;

class					System
{
public:
  static System				*getInstance();
  Entity				*createEntity();
  Entity				*getEntity(int id) const;
  DataComponent				*createComponent(int type);
  template				<typename T>
  T					*createComponent(int type);
  template				<typename T>
  T					*getComponent(int entityId, int type) const;

  template				<typename T>
  T					*getComponent(Entity *entityPtr, int type) const;

  template				<typename T>
  T					*getComponent(DataComponent *componentBrother, int type) const;

  void					registerComponentType(int type, AComponent *component);
  template				<typename T>
  T					*type(int type) const;
  ~System();
private:
  System();
private:
  std::map<int, Entity*>		entityList_;
  // std::map<int, Component*>		componentList_;
  // std::multimap<int, Component*>	unsuedComponentList_;

  typedef std::map<int, Entity*>::iterator			t_iter_entitylist;
  typedef std::map<int, Entity*>::const_iterator		t_const_iter_entitylist;
  // typedef std::map<int, Component*>::iterator			t_iter_componentlist;
  // typedef std::map<int, Component*>::const_iterator		t_const_iter_componentlist;
  // typedef std::multimap<int, Component*>::iterator		t_iter_unusedComponentlist;
  // typedef std::multimap<int, Component*>::const_iterator	t_const_iter_unusedComponentlist;

  typedef std::pair<int, Entity*>				t_pair_entity;
  // typedef std::pair<int, Component*>				t_pair_component;
};

#endif					// __SYSTEM_HH__
