#ifndef				__TEXTURE_COMPONENT_HPP__
# define			__TEXTURE_COMPONENT_HPP__

#include			"Component.hpp"
#include			"ObjModelMedia.hpp"

struct				Texture : public Component<Texture>
{
  TextureMediaPtr		texture;

  Texture			&operator=(const Texture &o)
  {
    texture = o.texture;
    return *this;
  }

  void				setTexture(const std::string & name)
  {
    texture = ResourceManager::getInstance().get<TextureMedia>(name);
  }
};

#endif				// __TEXTURE_COMPONENT_HPP__

