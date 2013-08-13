#ifndef					__POSITION_HH__
# define				__POSITION_HH__

#include				"Component.hh"
#include				"Entity.hh"
#include				"ComponentTypes.hh"

namespace				ComponentType
{
  struct				DataPosition : public DataComponent
  {
    double				x;
    double				y;
    DataPosition(int typeId, AComponent *component);
  };

  class					Position : public AComponent
  {
  public:
    Position();
    virtual ~Position();
    static Position			*getInstance();
    virtual void			init(Entity *entity );
    virtual void			update(Entity *entity, double time = 0);
    Position				*operator()(Entity *entity);
    Position				*operator()();
    int					getX(Entity *entity) const;
  private:
    int					typeId_;
  };
};

#endif					// __POSITION_HH__
