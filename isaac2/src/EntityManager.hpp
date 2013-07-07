#ifndef				__ENTITY_MANAGER_HPP__
# define			__ENTITY_MANAGER_HPP__

#include			<vector>
#include			<bitset>

#include			"Singleton.hpp"

struct				EntityData
{
  std::bitset<64>		components;
  unsigned int			id;

  EntityData(unsigned int entityId)
  {
    components.reset();
    id = entityId;
  }
};

class				EntityManager : public Singleton<EntityManager>
{
public:
  unsigned int			newEntity()
  {
    unsigned int		res;

    if (freeIds_.empty())
      {
	list_.push_back(EntityData(idCounter_));
	res = idCounter_;
	++idCounter_;
	return res;
      }
    res = freeIds_.back();
    freeIds_.pop_back();
    return res;
  }

  void				eraseEntity(unsigned int id)
  {
    list_[id].components.reset();
    freeIds_.push_back(id);
  }

  EntityData			&getEntityData(unsigned int id)
  {
    return list_[id];
  }

private:
  unsigned int			idCounter_;
  std::vector<EntityData>	list_;
  std::vector<unsigned int>	freeIds_;
private:
  friend class Singleton<EntityManager>;
  EntityManager(): idCounter_(1)
  {
  };
  virtual ~EntityManager(){};
};

#endif				// __ENTITY_MANAGER_HPP__
