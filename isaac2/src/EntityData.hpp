#ifndef				__ENTITY_DATA_HPP__
# define			__ENTITY_DATA_HPP__

#include			<bitset>
#include			<string>
#include			"Exception.hh"
#include			"TagIdManager.hpp"

#define				TAG_LENGTH (32)
#define				LAYER_LENGTH (32)
#define				DEFAULT_TAG ("Default")
#define				DEFAULT_LAYER ("Default")

struct				EntityData
{
  std::bitset<64>		components;
  unsigned int			id;
  bool				active;
private:
  unsigned int			tag_;
  unsigned int			layer_;

public:
  EntityData(unsigned int entityId = 0,
	     bool active = false,
	     const std::string & tag = DEFAULT_TAG,
	     const std::string & layer = DEFAULT_LAYER)
  {
    components.reset();
    id = entityId;
    active = active;
    if (tag.size() > TAG_LENGTH)
      {
	throw TagToLong(entityId, tag, true);    
      }
    tag_ = TagIdManager::getInstance().getTagId(tag);
    if (layer.size() > LAYER_LENGTH)
      {
	throw TagToLong(entityId, layer, false);    
      }
    layer_ = TagIdManager::getInstance().getTagId(layer);
  }

  EntityData			&operator=(const EntityData &o)
  {
    components = o.components;
    id = o.id;
    active = o.active;
    tag_ = o.tag_;
    layer_ = o.layer_;
    return *this;
  }

  unsigned int			&getTag()
  {
    return tag_;
  }

  unsigned int			&getLayer()
  {
    return layer_;
  }

  void				setTag(const std::string & tag)
  {
    tag_ = TagIdManager::getInstance().getTagId(tag);
  }

  void				setLayer(const std::string & layer)
  {
    layer_ = TagIdManager::getInstance().getTagId(layer);
  }


};

#endif				// __ENTITY_DATA_HPP__
