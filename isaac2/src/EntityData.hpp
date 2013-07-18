#ifndef				__ENTITY_DATA_HPP__
# define			__ENTITY_DATA_HPP__

#include			<bitset>

struct				EntityData
{
  std::bitset<64>		components;
  unsigned int			id;
  bool				active;

  EntityData(unsigned int entityId = 0, bool active = false)
  {
    components.reset();
    id = entityId;
    active = active;
  }

  EntityData			&operator=(const EntityData &o)
  {
    components = o.components;
    id = o.id;
    active = o.active;
    return *this;
  }

};

#endif				// __ENTITY_DATA_HPP__
