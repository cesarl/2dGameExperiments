#include			"EntityManager.hpp"
#include			"SystemManager.hpp"

#define				RESERVE_ENTITY (100)

unsigned int			EntityManager::newEntity()
{
  unsigned int		res;

  if (freeIds_.empty())
    {
      if (list_.size() <= idCounter_)
	list_.resize(idCounter_ + RESERVE_ENTITY);
      list_[idCounter_] = EntityData(idCounter_);
      res = idCounter_;
      ++idCounter_;
      return res;
    }
  res = freeIds_.back();
  freeIds_.pop_back();
  return res;
}

// void				EntityManager::update(float time, const ALLEGRO_EVENT &ev)
// {
//   std::vector<EntityData>::iterator it = ++list_.begin();
//   unsigned int			i = 1;

//   while (i < idCounter_ && it != list_.end())
//     {
//       SystemManager::getInstance().update(*it, time, ev);	
//       ++it;
//       ++i;
//     }
//   (void)time;
//   (void)(ev);
// }

void				EntityManager::eraseEntity(unsigned int id)
{
  list_[id].components.reset();
  freeIds_.push_back(id);
  // std::cout << id << std::endl;
}

EntityData			&EntityManager::getEntityData(unsigned int id)
{
  return list_[id];
}


