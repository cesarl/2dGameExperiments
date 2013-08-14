#include			"EntityManager.hpp"
#include			"SystemManager.hpp"

#define				RESERVE_ENTITY (10000)

unsigned int			EntityManager::newEntity()
{
  unsigned int		res;

  if (freeIds_.empty())
    {
      if (list_.size() <= idCounter_)
	{
	  std::cout << "Resize list of size " << list_.size() << " -> " << idCounter_ + RESERVE_ENTITY << std::endl;
	  list_.resize(idCounter_ + RESERVE_ENTITY);
	}
      list_[idCounter_] = EntityData(idCounter_, true);
      res = idCounter_;
      ++idCounter_;
      return res;
    }
  res = freeIds_.back();
  freeIds_.pop_back();
  list_[res] = EntityData(res, true);
  return res;
}
