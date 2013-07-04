#ifndef				__COMPONENT_MANAGER_HPP__
# define			__COMPONENT_MANAGER_HPP__

#include			<vector>
#include			"Singleton.hpp"

class				ComponentManager : public Singleton<ComponentManager>
{
public:
  template			<class T>
  void				addComponent(unsigned int entity)
  {
    
  }
private:
  friend class Singleton<ComponentManager>;
  ComponentManager()
  {
  }
  virtual ~ComponentManager(){}
};

#endif				// __COMPONENT_MANAGER_HPP__
