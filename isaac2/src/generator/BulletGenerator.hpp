#ifndef				__BULLET_GENERATOR_HPP__
# define			__BULLET_GENERATOR_HPP__

#include			<vector>
#include			"EntityManager.hpp"
#include			"EntityManager.hpp"

class				BulletGenerator
{
public:
  BulletGenerator()
  {}

  ~BulletGenerator()
  {}

  void				clear()
  {
  }

  void				generate(Vector3d &position, Vector3d &)
  {
    (void)position;
  }
private:
};

#endif				// __BULLET_GENERATOR_HPP__
