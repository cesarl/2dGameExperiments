#ifndef				__MODEL_COMPONENT_HPP__
# define			__MODEL_COMPONENT_HPP__

#include			"Component.hpp"
#include			"ObjModel.hpp"

struct				Model : public Component<Model>
{
  ObjModelPtr			obj;

  Model				&operator=(const Model &o)
  {
    obj = o.obj;
    return *this;
  }
};

#endif				// __MODEL_COMPONENT_HPP__

