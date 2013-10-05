#ifndef				__COMPONENT_HPP__
# define			__COMPONENT_HPP__

static				int uniqueId()
{
  static int			id = 0;
  return id++;
}

struct              AComponent
{
	AComponent() {}
	virtual ~AComponent() {}
	virtual AComponent &operator=(const AComponent &o) { return *this; }
};

template			<class T>
struct				Component : public AComponent
{
  static unsigned int		getTypeId()
  {
    static unsigned int		 id = uniqueId();
    return id;
  }
};


#endif				// __COMPONENT_HPP__
