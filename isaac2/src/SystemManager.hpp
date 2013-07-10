#ifndef				__SYSTEM_MANAGER_HPP__
# define			__SYSTEM_MANAGER_HPP__

#include			<vector>
#include			<allegro5/allegro.h>
#include			"Singleton.hpp"
#include			"EntityData.hpp"
#include			"ComponentManager.hpp"

class				System
{
public:
  virtual ~System(){};
  virtual void			update(unsigned int, float, const ALLEGRO_EVENT &) = 0;

  template			<class T>
  void				require()
  {
    unsigned int		type = ComponentTypeManager::getInstance().getComponentType<T>();

    componentsRequired_[type] = 1;
  }

  bool				match(const EntityData &entity)
  {
    if (componentsRequired_.none())
      {
	throw SystemWithoutComponentRequired("System is empty : ", typeid(*this).name());
      }
    if ((entity.components & componentsRequired_) == componentsRequired_)
      return true;
    return false;
  }
protected:
  std::bitset<64>		componentsRequired_;
private:
  
};

class				ImageSystem : public System
{
public:
  virtual ~ImageSystem(){};
  ImageSystem()
  {}
virtual void			update(unsigned int entity, float, const ALLEGRO_EVENT &);

private:
};

class				VelocitySystem : public System
{
public:
  virtual ~VelocitySystem(){};
  VelocitySystem()
  {}
virtual void			update(unsigned int entity, float, const ALLEGRO_EVENT &);

private:
};


class				SystemManager : public Singleton<SystemManager>
{
public:

  void				add(System *sys);

void				update(const EntityData &entity , float time, const ALLEGRO_EVENT & ev);
private:
  std::vector<System*>		list_;
private:
  SystemManager()
  {}

  virtual ~SystemManager()
  {}
private:
  friend class Singleton<SystemManager>;
};

#endif				// __SYSTEM_MANAGER_HPP__
