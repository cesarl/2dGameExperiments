#ifndef				__ENTITY_MANAGER_HPP__
# define			__ENTITY_MANAGER_HPP__

#include			<vector>
#include			<bitset>
#include			<allegro5/allegro.h>
#include            <iostream>
#include			"Singleton.hpp"
#include			"EntityData.hpp"

class				EntityManager : public Singleton<EntityManager>
{
public:

EntityData			    &newEntity()
{
	unsigned int		res;

	if (freeIds_.empty())
	{
		if (list_.size() <= idCounter_)
		{
			throw new NoMoreEntityAvailable("No more entity available");
		}
		list_[idCounter_] = EntityData(idCounter_, true);
		res = idCounter_;
		++idCounter_;
		return list_[res];
	}
	res = freeIds_.back();
	freeIds_.pop_back();
	list_[res] = EntityData(res, true);
	return list_[res];
}

  inline void			eraseEntity(unsigned int id)
  {
    list_[id].components.reset();
    list_[id].active = false;
    freeIds_.push_back(id);
  }

  EntityData		&getEntityData(unsigned int id)
  {
    return list_[id];
  }

  inline unsigned int		&end()
  {
    return idCounter_;
  }

  std::vector<EntityData>	&getList()
  {
    return list_;
  }

bool init()
{
	if (RESERVE_ENTITY > list_.max_size())
		return false;
	list_.resize(idCounter_ + RESERVE_ENTITY);
	return true;
}

private:
  unsigned int			idCounter_;
  std::vector<EntityData>	list_;
  std::vector<unsigned int>	freeIds_;
private:
  friend class Singleton<EntityManager>;
  EntityManager(): idCounter_(0)
  {
  };
  virtual ~EntityManager(){};
};

#endif				// __ENTITY_MANAGER_HPP__
