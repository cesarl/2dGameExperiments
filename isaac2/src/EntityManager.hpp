#ifndef				__ENTITY_MANAGER_HPP__
# define			__ENTITY_MANAGER_HPP__

#include			<vector>
#include			"Singleton.hpp"

class				EntityManager : public Singleton<EntityManager>
{
public:
  unsigned int			newEntity()
  {
    unsigned int		res;

    if (freeIds_.empty())
      {
	list_.push_back(idCounter_);
	res = idCounter_;
	++idCounter_;
	return res;
      }
    res = freeIds_.back();
    list_[res] = res;
    freeIds_.pop_back();
    return res;
  }

  void				eraseEntity(unsigned int id)
  {
    list_[id] = 0;
    freeIds_.push_back(id);
  }

private:
  unsigned int			idCounter_;
  std::vector<unsigned int>	list_;
  std::vector<unsigned int>	freeIds_;
private:
  friend class Singleton<EntityManager>;
  EntityManager(): idCounter_(1)
  {
  };
  virtual ~EntityManager(){};
};

#endif				// __ENTITY_MANAGER_HPP__
