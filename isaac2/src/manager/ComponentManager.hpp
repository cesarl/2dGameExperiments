#ifndef				__COMPONENT_MANAGER_HPP__
# define			__COMPONENT_MANAGER_HPP__

#include			<vector>
#include			<map>
#include			<cstdlib>
// a retirer ensuite pour debug
#include			<csignal>

#include			"Singleton.hpp"
#include			"ComponentTypeManager.hpp"
#include			"EntityData.hpp"
#include			"EntityManager.hpp"
#include			"SystemManager.hpp"

#define				RESERVE_COMPONENT (10000)

class				ComponentManager : public Singleton<ComponentManager>
{
public:
  template			<class T>
  T				&addComponent(unsigned int entity)
  {
    std::vector<T>		*collection = getComponentCollection<T>();
    EntityData			&data = EntityManager::getInstance().getEntityData(entity);

    if (collection->size() <= entity)
      {
	collection->resize(entity + RESERVE_COMPONENT);
      }

    collection->at(entity) = T();
    data.components[T::getTypeId()] = 1;
    return collection->at(entity);
    // todo reinitialiser les  valeurs
  }

  template			<class T>
  T				&addComponent(EntityData &entity)
  {
    std::vector<T>		*collection = getComponentCollection<T>();

    if (collection->size() <= entity.id)
      {
	collection->resize(entity.id + RESERVE_COMPONENT);
      }

    collection->at(entity.id) = T();
    entity.components[T::getTypeId()] = 1;
    return collection->at(entity.id);
    // todo reinitialiser les  valeurs
  }

  template			<class T>
  inline void			removeComponent(unsigned int entity)
  {
    EntityData			&data = EntityManager::getInstance().getEntityData(entity);

    //if (std::string(typeid(T).name()) != "9Collision")
      //{
	//std::cout << "BEFORE " << entity << " " << data.id << " -> " << data.components << std::endl;
//      }
    data.components[T::getTypeId()] = 0;
    //if (std::string(typeid(T).name()) != "9Collision")
      //std::cout << "AFTER " << entity << " " << data.id << " -> " << data.components << std::endl;
    // todo resseter les valeurs par defauts
  }

  template			<class T>
  inline void			removeComponent(EntityData &entity)
  {
    entity.components[T::getTypeId()] = 0;
    // todo resseter les valeurs par defauts
  }

  template			<class T>
  inline T			*getComponent(unsigned int entity)
  {
    EntityData			&data = EntityManager::getInstance().getEntityData(entity);

    if (data.components[T::getTypeId()] == 0)
      return NULL;

    std::vector<T>		*collection = getComponentCollection<T>();

    if (!collection)
      return NULL;
    if (collection->capacity() <= entity)
      return NULL;
    return &(collection->at(entity));
  }

  template			<class T>
  inline T			*getComponent(const EntityData &entity)
  {
    if (entity.components[T::getTypeId()] == 0)
      {
	std::cout << "Pas possible c est pas dans mon code bar" << std::endl;
	std::cout << entity.components << " " << T::getTypeId() << " " << entity.id << std::endl;
	// raise(SIGINT);
	return NULL;
      }

    std::vector<T>		*collection = getComponentCollection<T>();

    if (!collection)
      {
	std::cout << "Pas possible j ai aps de collection" << std::endl;
	return NULL;
      }
    if (collection->capacity() <= entity.id)
      {
	std::cout << "Pas possible mon vector est trop petit" << std::endl;
	return NULL;
      }
    return &(collection->at(entity.id));
  }

  template			<class T>
  bool				hasComponent(unsigned int entity)
  {
    EntityData			&data = EntityManager::getInstance().getEntityData(entity);

    if (data.components[T::getTypeId()] == 0)
      return false;

    std::vector<T>		*collection = getComponentCollection<T>();

    if (!collection)
      return false;
    if (collection->capacity() <= entity)
      return false;
    return true;
  }

  template			<class T>
  bool				hasComponent(const EntityData &entity)
  {
    if (entity.components[T::getTypeId()] == 0)
      return false;

    std::vector<T>		*collection = getComponentCollection<T>();

    if (!collection)
      return false;
    if (collection->capacity() <= entity.id)
      return false;
    return true;
  }

  template			<class T>
  std::vector<T>		*getComponentCollection()
  {
    std::map<unsigned int, void*>::iterator it;
    std::vector<T>		*res;

    it = componentListCollection_.find(T::getTypeId());
    if (it != componentListCollection_.end())
      {
	res = (std::vector<T> *)(it->second);
	return res;
      }
    res = new std::vector<T>;
    componentListCollection_.insert(std::pair<unsigned int, void *>(T::getTypeId(), res));
    return res;
  }
private:
  std::map<unsigned int, void *>	componentListCollection_;
private:
  friend class Singleton<ComponentManager>;
  ComponentManager()
  {
  }
  virtual ~ComponentManager(){}
};

#endif				// __COMPONENT_MANAGER_HPP__
