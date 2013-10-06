#ifndef				__ENTITY_DATA_HPP__
# define			__ENTITY_DATA_HPP__

#include			<bitset>
#include			<string>
#include            <vector>
#include			"Exception.hh"
#include			"TagIdManager.hpp"
#include            "Component.hpp"
#include            "Components.hpp"
#include            "Configurations.h"

struct				EntityData
{
	std::bitset<COMPONENT_MAX_NUMBER>		components;
	std::vector<AComponent*>                componentsPtr;
	unsigned int			id;
	bool  				active;
private:
	unsigned int			tag_;
	unsigned int			layer_;

public:
	EntityData(unsigned int entityId = 0,
		bool active = false,
		const std::string & tag = DEFAULT_TAG,
		const std::string & layer = DEFAULT_LAYER);

	EntityData			&operator=(const EntityData &o)
	{
		reset();
		components = o.components;
		componentsPtr = o.componentsPtr;
		id = o.id;
		active = o.active;
		tag_ = o.tag_;
		layer_ = o.layer_;
		return *this;
	}

	EntityData(const EntityData &o)
	{
		reset();
		components = o.components;
		componentsPtr = o.componentsPtr;
		id = o.id;
		active = o.active;
		tag_ = o.tag_;
		layer_ = o.layer_;
		//*this = o;
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
			return getComponent<T>();

		T *tmp = new T;
		// todo assert on new T failed
		//if (!tmp)

		components[T::getTypeId()] = 1;
		componentsPtr[T::getTypeId()] = tmp;
		return tmp;
	}

	~EntityData()
	{
		componentsPtr.clear();
	}

	void reset()
	{
		for (std::vector<AComponent*>::iterator it = std::begin(componentsPtr); it != std::end(componentsPtr); ++it)
		{
			delete *it;
		}
		componentsPtr.clear();
	}

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
	inline T			*getComponent() const
	{

		if (T::getTypeId() > componentsPtr.size())
		{
			std::cout << "Taht is not normal ! " << std::endl;
		}
		return static_cast<T*>(componentsPtr[T::getTypeId()]);
	}

	template			<class T>
	bool				hasComponent() const
	{
		return (components[T::getTypeId()] != 0);
	}
};

#endif				// __ENTITY_DATA_HPP__
