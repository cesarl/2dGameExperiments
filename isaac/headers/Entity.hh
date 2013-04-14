#ifndef					__ENTITY_HH__
# define				__ENTITY_HH__

#include				<map>
#include				<list>
#include				<fstream>
#include				<allegro5/allegro.h>
#include				"Component.hh"

class					AComponent;

class					Entity
{
public:
  Entity();
  virtual ~Entity();
  int					getId() const;
  void					setId(int id);
  AComponent				*getComponent(int type) const;
  void					addComponent(AComponent *component);
  void					removeComponent(int type);
  void					update();
  void					draw();
  virtual void				serialize(std::ofstream *file);
  virtual void				unserialize(std::ifstream *file);
  virtual void				generate(int seed = 0);
protected:
  int					id_;
  std::map<int, AComponent*>		list_;
  std::list< std::pair<int, AComponent*> > updatePriorityList_;
  AComponent				*drawable_;
  int					seed_;

  typedef std::map<int, AComponent*>::iterator	t_iter;
  typedef std::map<int, AComponent*>::const_iterator t_const_iter;
  typedef std::pair<int, AComponent*>		t_pair;

  typedef std::list< std::pair<int, AComponent*> >::iterator		t_prio_iter;
  typedef std::list< std::pair<int, AComponent*> >::const_iterator	t_prio_const_iter;
public:

  //
  // templated member functions
  //

  template				<typename T>
  T					*getComponent(int type)
  {
    t_const_iter			it;
    T					*tmp;

    it = this->list_.find(type);
    if (it != this->list_.end())
      return static_cast<T*>(it->second);
    tmp = new T(this);
    this->addComponent(tmp);
    return tmp;
  }
};

#endif					// __ENTITY_HH__
