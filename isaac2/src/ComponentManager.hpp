#ifndef				__COMPONENT_MANAGER_HPP__
# define			__COMPONENT_MANAGER_HPP__

#include			<vector>
#include			<map>
#include			<typeinfo>
#include			<iostream>

#include			"Singleton.hpp"
#include			"ComponentTypeManager.hpp"

struct				Position
{
  Vector3d			position_;
};

class				ComponentManager : public Singleton<ComponentManager>
{
public:
  template			<class T>
  T				&addComponent(unsigned int entity)
  {
    std::vector<T>		&collection = getComponentCollection<T>();
    EntityData			&data = EntityManager::getInstance().getEntityData(entity);
    unsigned int		type = ComponentTypeManager::getInstance().getComponentType<T>();

    if (collection.capacity() <= entity)
      collection.resize(entity + 1);

    collection.at(entity) = T();

    data.components[type] = 1;
    std::cout << type << "    " << data.components << std::endl;
    return collection[entity];
    // todo reinitialiser les  valeurs
  }

  template			<class T>
  void				removeComponent(unsigned int entity)
  {
    EntityData			&data = EntityManager::getInstance().getEntityData(entity);
    unsigned int		type = ComponentTypeManager::getInstance().getComponentType<T>();

    data.components[type] = 0;
    // todo resseter les valeurs par defauts
  }

  // template			<class T>
  // T				*getComponent(unsigned int entity)
  // {
  //   unsigned int		type = ComponentTypeManager::getInstance().getComponentType<T>();
  //   std::vector<T>		&collection = getComponentCollection<T>();

  //   if (collection.capacity() <= entity)
  //     collection.resize(entity + 1);
    
  //   collection.at(entity) = T();
  //   return collection[entity];
  // }

  template			<class T>
  std::vector<T>		&getComponentCollection()
  {
    std::vector<T>		*res;
    res = (std::vector<T> *)(componentListCollection_[typeid(T).name()]);

    if (!res)
      {
	res = new std::vector<T>();
	componentListCollection_.insert(std::pair<const char *, void *>(typeid(T).name(), res));
	return *res;
      }
    return *res;
  }
private:
  std::map<const char *, void *>	componentListCollection_;
private:
  friend class Singleton<ComponentManager>;
  ComponentManager()
  {
  }
  virtual ~ComponentManager(){}
};

#endif				// __COMPONENT_MANAGER_HPP__
