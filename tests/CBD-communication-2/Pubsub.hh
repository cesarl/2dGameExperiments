#ifndef					__PUBSUB_HH__
# define				__PUBSUB_HH__

#include			<string>
#include			<iostream>
#include			<list>
#include			<map>
#include			"AComponent.hh"

class					AComponent;

class					Pubsub
{
public:
  ~Pubsub();
private:
  Pubsub();
public:
  static Pubsub				*getInstance();
  void					subscribe(AComponent * component, std::string const & message);
  void					publish(std::string const &message);
private:
  std::map<std::string, std::list<AComponent*> > map_;
  typedef std::pair<std::string, std::list<AComponent*> > t_pair_map;
  typedef std::map<std::string, std::list<AComponent*> >::iterator t_iter_map;
  typedef std::list<AComponent*>::iterator t_iter_list;
};

#endif					// __PUBSUB_HH__
