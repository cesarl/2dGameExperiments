#ifndef				__IMG_COMPONENT_HPP__
# define			__IMG_COMPONENT_HPP__

#include			"Component.hpp"
#include            "ImageMedia.hpp"

struct				Img : public Component<Img>
{
  ImageMediaPtr			img;

  Img				&operator=(const Img &o )
  {
    this->img = o.img;
    return *this;
  }
};

#endif				// __IMG_COMPONENT_HPP__
