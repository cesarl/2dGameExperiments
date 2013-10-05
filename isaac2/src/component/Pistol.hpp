#ifndef				__PISTOL_COMPONENT_HPP__
# define			__PISTOL_COMPONENT_HPP__

#include			<glm/glm.hpp>
#include			"Component.hpp"

struct				Pistol : public Component<Pistol>
{
  float				fireRate;
  float				fireRateCache;
  float				fireForce;
  int				fireType; // le type ne sert a rien pour le moment - il servira a changer de type de projectile
  glm::vec3			relativePosition;

  Pistol()
  {
    fireRate = 0.001f;
    fireRateCache = 0.0f;
    fireForce = 1.0f;
    fireType = 1.0f;
    relativePosition = glm::vec3(0.0f, 0.0f, 0.0f);
  };
};

#endif				// __PISTOL_COMPONENT_HPP__
