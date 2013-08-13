#ifndef				__SYSTEM_HPP__
#define				__SYSTEM_HPP__

#include			<set>

class				SystemManager;

class				System
{
  friend class			SystemManager;

public:
  virtual ~System(){};
  virtual void			update(EntityData & e, float, const ALLEGRO_EVENT &) = 0;
  virtual void			updateBegin(float, const ALLEGRO_EVENT &){};
  virtual void			updateEnd(float, const ALLEGRO_EVENT &){};
  virtual void			init() = 0;

  template			<class T>
  void				require()
  {
    componentsRequired_[T::getTypeId()] = 1;
  }

  bool				add(const EntityData & e)
  {
    if (match(e))
      {
	entities_ .insert(e.id);
	return true;
      }
    return false;
  }

  bool				remove(const EntityData & e)
  {
    std::set<unsigned int>::iterator it;
    if (!match(e) && (it = entities_.find(e.id)) != entities_.end())
      {
	entities_.erase(e.id);
	return true;
      }
    return false;
  }

  bool				match(const EntityData &entity)
  {
    if (componentsRequired_.none())
      {
	throw SystemWithoutComponentRequired("System is empty : ", typeid(*this).name());
      }
    if ((entity.components & componentsRequired_) == componentsRequired_)
      return true;
    return false;
  }

protected:
  std::bitset<64>		componentsRequired_;
  std::set<unsigned int>	entities_;
private:
  
};

#endif				// __SYSTEM_HPP__
