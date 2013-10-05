#ifndef				__POSITION_REGISTER_SYSTEM_HPP__
# define			__POSITION_REGISTER_SYSTEM_HPP__

#include			"Components.hpp"

// this system don't heritate form System class,
// it's a singleton who will be called by other position register sub-system

class				PositionRegisterSystem : public Singleton<PositionRegisterSystem>
{
public:
  virtual ~PositionRegisterSystem(){};
  PositionRegisterSystem()
  {}
private:
  unsigned int			cellSize_;
  std::vector<unsigned int>	*grid_;
  unsigned int			width_;
  unsigned int			height_;
};

#endif				// __POSITION_REGISTER_SYSTEM_HPP__
