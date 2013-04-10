#ifndef					__MOVE_HH__
# define				__MOVE_HH__

#include				"Component.hh"
#include				"Entity.hh"
#include				"ComponentTypes.hh"

namespace				ComponentType
{
  struct				DataMove : public DataComponent
  {
    double				vx;
    double				vy;
    double				gravityX;
    double				gravityY;
    double				frictionX;
    double				frictionY;
    DataMove(int typeId, AComponent *component);
  };

  class					Move : public AComponent
  {
  public:
    Move();
    virtual ~Move();
    static Move				*getInstance();
    virtual void			init(Entity *entity );
    virtual void			update(Entity *entity, double time = 0);
    Move				*operator()(Entity *entity);
    Move				*operator()();
  private:
    int					typeId_;
  };
};

#endif					// __MOVE_HH__
