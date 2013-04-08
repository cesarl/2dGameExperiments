#ifndef				__ACOMPONENT_HH__
# define			__ACOMPONENT_HH__

#include			<string>
#include			<iostream>
#include			<list>

#include			"Pubsub.hh"

class				Entity;
class				Pubsub;

class				AComponent
{
public:
  AComponent(int type);
  virtual ~AComponent();
  virtual void			update() = 0;
  int				getType() const;
  void				setEntity(Entity *entity);
  void				subscribe(std::string const & message);
  virtual void			receiveSubscription(std::string const & message);
protected:
  int				type_;
  Entity			*entity_;
};

#endif				// __ACOMPONENT_HH__
