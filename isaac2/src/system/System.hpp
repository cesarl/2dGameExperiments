#ifndef				__SYSTEM_HPP__
#define				__SYSTEM_HPP__

class				System
{
public:
  virtual ~System(){};
  virtual void			update(unsigned int, float, const ALLEGRO_EVENT &) = 0;
  virtual void			updateBegin() = 0;
  virtual void			updateEnd() = 0;
  virtual void			init() = 0;

  template			<class T>
  void				require()
  {
    unsigned int		type = ComponentTypeManager::getInstance().getComponentType<T>();

    componentsRequired_[type] = 1;
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
private:
  
};

#endif				// __SYSTEM_HPP__
