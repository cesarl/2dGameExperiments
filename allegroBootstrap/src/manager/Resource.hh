#ifndef					__RESOURCE_HH__
# define				__RESOURCE_HH__

#include				<string>

class					Resource
{
public:
  Resource();
  virtual ~Resource();
  const std::string			&getName() const;
  void					addRef();
  int					release();
private:
  // copy forbiden
  Resource(Resource &o);
  void					operator=(Resource &o);
private:
  std::string				name_;
  int					counter_;
  // friend class ResourceManager;
};

#endif					// __RESOURCE_HH__
