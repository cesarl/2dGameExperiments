#include				"Resource.hh"
#include				"ResourceManager.hpp"

Resource::Resource() :
  name_(""),
  counter_(1)
{}

Resource::~Resource()
{
  // todo retirer du ressource manager
}

const std::string			&Resource::getName() const
{
  return this->name_;
}

void					Resource::addRef()
{
  ++(this->counter_);
}

int					Resource::release()
{
  int					c = --(this->counter_);

  if (c == 0)
    delete this;
  return c;
}
