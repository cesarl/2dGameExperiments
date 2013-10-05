#ifndef				__ENTITY_MANAGER_HPP__
# define			__ENTITY_MANAGER_HPP__

#include			<vector>
#include			<bitset>
#include			<allegro5/allegro.h>
#include            <iostream>
#include			"Singleton.hpp"
#include			"EntityData.hpp"

#define				RESERVE_ENTITY (100)

class				EntityManager : public Singleton<EntityManager>
{
public:

EntityData			    &newEntity()
{
	unsigned int		res;

	if (isIterating_)
	{
		tmpList_.emplace_back(EntityData());
		return tmpList_.back();
	}

	if (freeIds_.empty())
	{
		while (list_.size() <= idCounter_)
		{
			std::cout << "Resize list of size " << list_.size() << " -> " << idCounter_ + RESERVE_ENTITY << std::endl;
			list_.resize(idCounter_ + RESERVE_ENTITY);
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

  inline unsigned int		end()
  {
    return idCounter_;
  }

  std::vector<EntityData>	&getList()
  {
    return list_;
  }

  void iterateBegin()
  {
	  isIterating_ = true;
  }

  void iterateEnd()
  {
	  isIterating_ = false;
	  for (std::vector<EntityData>::iterator it = std::begin(tmpList_); it != std::end(tmpList_); ++it)
	  {
		  placeEntity(*it);
	  }
	  tmpList_.clear();
  }


private:

	void			    placeEntity(EntityData &entity)
{
	unsigned int res;

	std::cout << entity.getLayer() << " " << TagIdManager::getInstance().getTagId("Good") <<  std::endl;

	if (freeIds_.empty())
	{
		while (list_.size() <= idCounter_ + 1)
		{
			std::cout << "Resize list end of loop of size " << list_.size() << " -> " << idCounter_ + RESERVE_ENTITY << std::endl;
			list_.resize(idCounter_ + RESERVE_ENTITY);
		}
		list_[idCounter_] = entity;
		entity.id = idCounter_;
		++idCounter_;
		return;
	}
	res = freeIds_.back();
	freeIds_.pop_back();
	list_[res] = entity;
	entity.id = res;
}


private:
  unsigned int			idCounter_;
  bool                  isIterating_;
  std::vector<EntityData>	list_;
  std::vector<unsigned int>	freeIds_;
  std::vector<EntityData> tmpList_;
private:
  friend class Singleton<EntityManager>;
  EntityManager(): idCounter_(0), isIterating_(false)
  {
  };
  virtual ~EntityManager(){};
};

#endif				// __ENTITY_MANAGER_HPP__
