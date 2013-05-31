#ifndef				__ENTITY_MANAGER_HH__
# define			__ENTITY_MANAGER_HH__

#include			<queue>
#include			<list>
#include			"Entity.hh"
#include			"DrawManager.hh"

class				EntityManager;

typedef bool			(*generationRule)(EntityManager *, int seed);

class				EntityManager
{
public:
  ~EntityManager();
  static EntityManager		*getInstance();
  bool				generate(int seed);
  void				clear();
  void				pushGenerationRule(generationRule fn);
  bool				serialize();
  bool				unserialize();
  void				update();
  void				draw();
  Entity			*create();
private:
  EntityManager();
  std::queue<generationRule>	generationRules_;
  std::list<Entity*>		list_;
};

#endif				// __ENTITY_MANAGER_HH__
