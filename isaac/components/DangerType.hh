#ifndef					__DANGER_TYPE_HH__
# define				__DANGER_TYPE_HH__

#include				"Component.hh"
#include				"Entity.hh"

typedef enum				t_dangerType
  {
    DAN_NONE,
    GOOD,
    BAD,
    BOTH
  }					t_dangerType;

class					DangerType : public AComponent
{
public:
  DangerType(Entity *entity);
  virtual ~DangerType();
  virtual void				update(double time = 0);
  virtual void				draw();
  t_dangerType				getType() const;
  void					setType(t_dangerType type);
private:
  t_dangerType				type_;
};

#endif					// __DANGER_TYPE_HH__
