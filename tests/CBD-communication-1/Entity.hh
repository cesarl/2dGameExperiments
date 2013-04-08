#ifndef				__ENTITY_HH__
# define			__ENTITY_HH__

#include			<string>
#include			<iostream>
#include			<list>
#include			"AComponent.hh"

class				AComponent;

class				Entity
{
public:
  Entity(std::string const & name);
  ~Entity();
  void				update();
  AComponent			*getComponent(int type) const;
  void				addComponent(AComponent *component);
  const std::string		&getName() const;
private:
  std::string			name_;
  std::list<AComponent*>	list_;
  typedef std::list<AComponent*>::iterator t_iter;
  typedef std::list<AComponent*>::const_iterator t_const_iter;
};

#endif				// __ENTITY_HH__
