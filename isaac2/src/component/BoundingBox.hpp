#ifndef				__BB_COMPONENT_HPP__
# define			__BB_COMPONENT_HPP__

#include			<glm/glm.hpp>
#include			"Component.hpp"

struct				BoundingBox : public Component<BoundingBox>
{
  glm::vec3			offset;
  glm::vec3			size;
  glm::vec3			from;
  glm::vec3			to;
  glm::vec3			pastFrom;
  glm::vec3			pastTo;
  void				set(const glm::vec3 & asize, const glm::vec3 & aoffset = glm::vec3(0.0f, 0.0f, 0.0f))
  {
    offset = aoffset;
    size = asize;
  }
};

#endif				// __BB_COMPONENT_HPP__
