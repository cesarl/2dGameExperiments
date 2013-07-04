#ifndef				__SYSTEM_MANAGER_HPP__
# define			__SYSTEM_MANAGER_HPP__

#include			<vector>
#include			"Singleton.hpp"

class				System
{
public:
  virtual ~System(){};
  virtual void			update(float, const ALLEGRO_EVENT &)
  {}
  System()
  {}
private:
};

class				ImageSystem : public System
{
public:
  virtual ~ImageSystem(){};
  ImageSystem()
  {}
  virtual void			update(float, const ALLEGRO_EVENT &)
  {}
private:
};

class				SystemManager : public Singleton<SystemManager>
{
public:

  template			<class T>
  void				test()
  {
    SmartPtr<T>			ptr;

    ptr = new T;
    (void)ptr;

    list_.push_back(T());
  }
private:
  std::vector<System>		list_;
private:
  SystemManager()
  {}

  virtual ~SystemManager()
  {}
private:
  friend class Singleton<SystemManager>;
};

#endif				// __SYSTEM_MANAGER_HPP__
