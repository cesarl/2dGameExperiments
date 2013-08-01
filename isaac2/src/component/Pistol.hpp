#ifndef				__PISTOL_COMPONENT_HPP__
# define			__PISTOL_COMPONENT_HPP__

struct				Pistol
{
  float				fireRate;
  float				fireRateCache;
  float				fireForce;
  int				fireType; // le type ne sert a rien pour le moment - il servira a changer de type de projectile
  Vector3d			relativePosition;

  Pistol()
  {
    fireRate = 0.01f;
    fireRateCache = 0.0f;
    fireForce = 1.0f;
    fireType = 1.0f;
    relativePosition = Vector3d(0.0f, 0.0f, 0.0f);
  };
};

#endif				// __PISTOL_COMPONENT_HPP__
