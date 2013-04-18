#ifndef				__DRAW_COLLECTION_HH__
# define			__DRAW_COLLECTION_HH__

#include			<list>
#include			<map>
#include			"Entity.hh"
#include			"ComponentTypes.hh"

class				DrawCollection
{
public:
  DrawCollection();
  virtual ~DrawCollection();
  void				clear();
  void				draw(ALLEGRO_EVENT *event = NULL);
  void				add(Entity *entity, int layer = 0);
  void				remove(Entity *entity);
protected:
  std::multimap<unsigned long, Entity*>		go_;
};

#endif				// __DRAW_COLLECTION_HH__
