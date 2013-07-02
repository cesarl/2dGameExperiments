#ifndef				__ANIMATION_MANAGER_HPP__
# define			__ANIMATION_MANAGER_HPP__

#include			<map>
#include			<string>

class				AnimationManager
{
public:
  static AnimationManager	&getInstance()
  {
    return			that_;
  }
  bool				initialize()
  {
    return true;
  }
  void				deinitialize()
  {}

private:
  // methods
  AnimationManager();
  ~AnimationManager();
  // attributes
  static AnimationManager	that_;
  std::map<std::string, IAnimation*> refs_;
};

#endif				// __ANIMATION_MANAGER_HPP__
