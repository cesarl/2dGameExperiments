#ifndef				__BB_COMPONENT_HPP__
# define			__BB_COMPONENT_HPP__

#include			"Component.hpp"

struct				BoundingBox : public Component<BoundingBox>
{
  Vector3d			offset;
  Vector3d			size;
  Vector3d			from;
  Vector3d			to;
  Vector3d			pastFrom;
  Vector3d			pastTo;
  void				set(const Vector3d & asize, const Vector3d & aoffset = Vector3d(0.0f, 0.0f, 0.0f))
  {
    offset = aoffset;
    size = asize;
  }
};

#endif				// __BB_COMPONENT_HPP__
