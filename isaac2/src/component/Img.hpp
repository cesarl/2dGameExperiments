#ifndef				__IMG_COMPONENT_HPP__
# define			__IMG_COMPONENT_HPP__

struct				Img
{
  ImagePtr			img;

  Img				operator=(Img)
  {
    return *this;
  }
};

#endif				// __IMG_COMPONENT_HPP__
