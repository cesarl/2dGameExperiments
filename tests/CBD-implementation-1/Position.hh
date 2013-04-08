#ifndef					__POSITION_HH__
# define				__POSITION_HH__

#include				"Component.hh"
#include				"System.hh"
#include				"Entity.hh"

namespace				ComponentType
{
  struct				DataPosition : public DataComponent
  {
    int					x;
    int					y;
  };

  class					Position : public AComponent
  {
  public:
    Position();
    virtual ~Position();
    static Position			*getInstance();
    virtual void			init(Entity *entity );
    virtual void			update(Entity *entity);
    Position				*operator()(Entity *entity);
    Position				*operator()();
    int					getX(Entity *entity) const;
  private:
    int					typeId_;
  };
};

#endif					// __POSITION_HH__
