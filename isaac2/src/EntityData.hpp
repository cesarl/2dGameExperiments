#ifndef				__ENTITY_DATA_HPP__
# define			__ENTITY_DATA_HPP__

#include			<bitset>

struct				EntityData
{
  std::bitset<64>		components;
  unsigned int			id;

  EntityData(unsigned int entityId = 0)
  {
    components.reset();
    id = entityId;
  }
};

#endif				// __ENTITY_DATA_HPP__
