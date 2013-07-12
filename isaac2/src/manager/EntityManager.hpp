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
  void				eraseEntity(unsigned int id);
  EntityData			&getEntityData(unsigned int id);
  iterator			&begin()
  {
    static iterator		it;

    it = list_.begin();
    return it;
  }
  iterator			&end()
  {
    static iterator		it;

    it = list_.end();    
    return it;
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
