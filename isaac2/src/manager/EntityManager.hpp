#ifndef				__ENTITY_MANAGER_HPP__
# define			__ENTITY_MANAGER_HPP__

#include			<vector>
#include			<bitset>
#include			<allegro5/allegro.h>
#include			"Singleton.hpp"
#include			"EntityData.hpp"

class				EntityManager : public Singleton<EntityManager>
{
public:
  typedef std::vector<EntityData>::iterator iterator;

  unsigned int			newEntity();
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
