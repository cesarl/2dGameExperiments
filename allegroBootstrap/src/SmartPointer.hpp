#ifndef					__SMART_POINTER_HPP__
#define					__SMART_POINTER_HPP__

#include				<cstdlib>
#include				"Exception.hh"

template				<class T>
class					SmartPtr
{
public:
  SmartPtr() :
    data_(NULL),
    counter_(NULL)
  {
  }

  SmartPtr(const SmartPtr<T> & o) :
    data_(o.data_),
    counter_(o.counter_)
  {
    if (this->counter_)
      ++(*this->counter_);
  }

  SmartPtr(T *ptr) :
    data_(ptr),
    counter_(new int(1))
  {}

  ~SmartPtr()
  {
    if (this->counter_ && (--(this->counter_) == 0))
      {
	delete this->counter_;
	delete this->data_;
      }
  }

  T					&operator *()
  {
    Assert(this->data_ != NULL);
    return *(this->data_);
  }

  T					*operator ->()
  {
    Assert(this->data_ != NULL);
    return this->data_;
  }

  const SmartPtr			&operator =(SmartPtr<T> ptr)
  {
    this->swap(ptr);
    return *this;
  }

  operator				T*() const
  {
    return this->data_;
  }
private:
  void					swap(SmartPtr<T> &ptr)
  {
    std::swap(this->data_, ptr.data);
    std::swap(this->counter_, ptr.counter_);
  }
private:
  T					*data_;
  int					*counter_;
};

#endif					// __SMART_POINTER_HPP__
