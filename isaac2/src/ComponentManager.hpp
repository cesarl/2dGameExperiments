#ifndef				__COMPONENT_MANAGER_HPP__
# define			__COMPONENT_MANAGER_HPP__

#include			<vector>
#include			<map>
#include			<typeinfo>
#include			<iostream>

#include			"Singleton.hpp"
#include			"ComponentTypeManager.hpp"
#include			"Image.hpp"
#include			"EntityData.hpp"
#include			"EntityManager.hpp"

struct				Position
{
  Vector3d			position;
};

struct				Img
{
  ImagePtr			img;

  Img				operator=(Img)
  {
    return *this;
  }
};


class				ComponentManager : public Singleton<ComponentManager>
{
public:
  template			<class T>
  T				&addComponent(unsigned int entity)
  {
    std::vector<T>		*collection = getComponentCollection<T>();
    EntityData			&data = EntityManager::getInstance().getEntityData(entity);
    unsigned int			type = ComponentTypeManager::getInstance().getComponentType<T>();

    if (collection->capacity() <= entity)
      {
	collection->resize(entity + 1);
      }

    collection->at(entity) = T();
    std::cout << "je rajout un composant de type " << type << " a lentite numero " << entity << "au numero " << data.id << std::endl;
    data.components[type] = 1;
    std::cout << type << "    " << data.components << std::endl;
    return collection->at(entity);
    // todo reinitialiser les  valeurs
  }

  template			<class T>
  void				removeComponent(unsigned int entity)
  {
    EntityData			&data = EntityManager::getInstance().getEntityData(entity);
    unsigned int			type = ComponentTypeManager::getInstance().getComponentType<T>();

    data.components[type] = 0;
    // todo resseter les valeurs par defauts
  }

  template			<class T>
  T				*getComponent(unsigned int entity)
  {
    std::vector<T>		*collection = getComponentCollection<T>();

    if (collection->capacity() <= entity)
      return NULL;
    return &(collection->at(entity));
  }

  template			<class T>
  std::vector<T>		*getComponentCollection()
  {
    std::map<const char *, void*>::iterator it;
    std::vector<T>		*res;

    it = componentListCollection_.find(typeid(T).name());
    if (it != componentListCollection_.end())
      {
	res = (std::vector<T> *)(it->second);
	return res;
      }
    res = new std::vector<T>;
    componentListCollection_.insert(std::pair<const char *, void *>(typeid(T).name(), res));
    return res;
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
