#ifndef				__ENTITY_DATA_HPP__
# define			__ENTITY_DATA_HPP__

#include			<bitset>
#include			<string>
#include            <vector>
#include			"Exception.hh"
#include			"TagIdManager.hpp"
#include            "Component.hpp"

#define				TAG_LENGTH (32)
#define				LAYER_LENGTH (32)
#define				DEFAULT_TAG ("Default")
#define				DEFAULT_LAYER ("Default")
#define             COMPONENT_MAX_NUMBER (64)

struct				EntityData
{
	std::bitset<COMPONENT_MAX_NUMBER>		components;
	std::vector<Component*>                 componentsPtr;
	unsigned int			id;
	bool  				active;
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
		componentsPtr.resize(COMPONENT_MAX_NUMBER);
		std::fill(std::begin(componentsPtr), std::end(componentsPtr), NULL);
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
		componentsPtr = o.componentsPtr;
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

	template			<class T>
	T    				*addComponent()
	{
		if (hasComponent<T>())
			return componentsPtr[T::getTypeId()];

		T *tmp = new T;
		// todo assert on new T failed
		//if (!tmp)

		components[T::getTypeId()] = 1;
		componentsPtr[T::getTypeId()] = tmp;
		return tmp;
	}

	//template			<class T>
	//T    				&addComponent()
	//{
	//	if (hasComponent<T>())
	//		return componentsPtr[T::getTypeId()];

	//	T *tmp = new T;
	//	// todo assert on new T failed
	//	//if (!tmp)

	//	components[T::getTypeId()] = 1;
	//	componentsPtr[T::getTypeId()] = tmp;
	//	return *tmp;
	//}

	template			<class T>
	inline void			removeComponent()
	{
		components[T::getTypeId()] = 0;
		delete componentsPtr[T::getTypeId()];
		componentsPtr[T::getTypeId()] = NULL;

		// todo
		// update systems entity list
	}

	template			<class T>
	inline T			*getComponent()
	{
		// we don't have to check if component exists
		//		if (!hasComponent())
		//			return NULL;
		return componentsPtr[T::getTypeId()];
	}

	template			<class T>
	bool				hasComponent()
	{
		return (components[T::getTypeId()] != 0);
	}
};

#endif				// __ENTITY_DATA_HPP__
