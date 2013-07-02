#ifndef				__ENTITY_MANAGER_HPP__
# define			__ENTITY_MANAGER_HPP__

#include			<vector>
#include			"Singleton.hpp"
#include			"Entity.hpp"

class				EntityManager : public Singleton<EntityManager>
{
public:
  unsigned int			newEntity()
  {
    unsigned int		res;

    if (freeIds_.empty())
      {
	list_.push_back(Entity(idCounter_));
	res = idCounter_;
	++idCounter_;
	return res;
      }
    res = freeIds_.back();
    list_[res] = Entity(res);
    freeIds_.pop_back();
    return res;
  }

  void				eraseEntity(unsigned int id)
  {
    list_.erase(list_.begin() + (id - 1));
    freeIds_.push_back(id);
  }

  template			<class Model>
  unsigned int			newComponent()
  {
    return ++idCounter_;
  }

private:
  unsigned int			idCounter_;
  std::vector<Entity>		list_;
  std::vector<unsigned int>	freeIds_;
private:
  friend class Singleton<EntityManager>;
  EntityManager(): idCounter_(0)
  {
  };
  virtual ~EntityManager(){};
};

#endif				// __ENTITY_MANAGER_HPP__
