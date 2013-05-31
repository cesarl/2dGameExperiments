#ifndef				__GENERATION_RULES_HH__
# define			__GENERATION_RULES_HH__

#include			"ComponentTypes.hh"
#include			"EntityManager.hh"

# define			CELL_SIZE (64)

bool				gnRoom(EntityManager *mgr, int seed);
bool				gnPnj(EntityManager *mgr, int seed);
bool				gnHeros(EntityManager *mgr, int seed);

#endif				// __GENERATION_RULES_HH__
