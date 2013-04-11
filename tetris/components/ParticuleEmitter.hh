#ifndef					__PARTICULE_EMITTER_HH__
# define				__PARTICULE_EMITTER_HH__

#include				<vector>
#include				<string>
#include				"Component.hh"
#include				"Entity.hh"

class					ParticuleEmitter : public AComponent
{
public:
  ParticuleEmitter(Entity *entity);
  virtual ~ParticuleEmitter();
  virtual void				update(double time = 0);
  virtual void				draw();
  void					config(std::string imagePath,
					       int columnNumber,
					       int partWidth,
					       int partHeight,
					       unsigned int possibleFrom,
					       unsigned int stepNumber,
					       double speed,
					       int flow,
					       int width,
					       int height);
  void					setWidth(int width);
  void					setHeight(int height);
public:
private:
  int					width_;
  int					height_;
  int					flow_;
  std::vector<Entity*>			list_;
  typedef std::vector<Entity*>::iterator	t_iter;
};

#endif					// __PARTICULE_EMITTER_HH__
