#include "EntityData.hpp"

EntityData::EntityData(unsigned int entityId,
					   bool active,
					   const std::string & tag,
					   const std::string & layer)
{
	components.reset();
	componentsPtr.resize(COMPONENT_MAX_NUMBER);
	//std::fill(std::begin(componentsPtr), std::end(componentsPtr), NULL);
	id = entityId;
	this->active = active;
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