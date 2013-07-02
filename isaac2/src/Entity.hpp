#ifndef				__ENTITY_HPP__
# define			__ENTITY_HPP__

#include			"Vector3d.hh"

struct				Entity
{
  unsigned int			id;
  Vector3d			position;
  Vector3d			rotation;
  Vector3d			scale;
  Entity(unsigned int pId,
	 const Vector3d & pPosition = Vector3d(0,0,0),
	 const Vector3d & pRotation = Vector3d(0,0,0),
	 const Vector3d & pScale = Vector3d(0,0,0)) :
    id(pId),
    position(pPosition),
    rotation(pRotation),
    scale(pScale)
  {}
};

#endif				// __ENTITY_HPP__
