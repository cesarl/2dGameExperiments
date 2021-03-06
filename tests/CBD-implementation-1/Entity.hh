#ifndef					__ENTITY_HH__
# define				__ENTITY_HH__

#include				<map>
#include				<list>
#include				<allegro5/allegro.h>
#include				"Component.hh"

struct					DataComponent;

class					Entity
{
public:
  Entity();
  ~Entity();
  int					getId() const;
  void					setId(int id);
  DataComponent				*getComponent(int type) const;
  void					addComponent(DataComponent *component);
  void					update();

private:
  int					id_;
  std::map<int, DataComponent*>		list_;
  std::list< std::pair<int, DataComponent*> > updatePriorityList_;

  typedef std::map<int, DataComponent*>::iterator	t_iter;
  typedef std::map<int, DataComponent*>::const_iterator t_const_iter;
  typedef std::pair<int, DataComponent*>		t_pair;

  typedef std::list< std::pair<int, DataComponent*> >::iterator		t_prio_iter;
  typedef std::list< std::pair<int, DataComponent*> >::const_iterator	t_prio_const_iter;
public:

  //
  // templated member functions
  //

  template				<typename T>
  T					*getComponent(int type) const
  {
    t_const_iter				it;

    it = this->list_.find(type);
    if (it == this->list_.end())
      return 0;
    return static_cast<T*>(it->second);
  }
};

#endif					// __ENTITY_HH__
