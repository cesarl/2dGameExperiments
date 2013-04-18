#include			<algorithm>
#include			"DrawCollection.hh"


DrawCollection::DrawCollection()
{
}

DrawCollection::~DrawCollection()
{
  this->clear();
}

void				DrawCollection::clear()
{
  this->go_.clear();
}


void				DrawCollection::draw(ALLEGRO_EVENT *event)
{
  std::multimap<unsigned long, Entity*>::iterator it;

  it = this->go_.begin();
  while (it != this->go_.end())
    {
      it->second->draw();
      ++it;
    }
  this->go_.clear();
  (void)event;
}

void				DrawCollection::add(Entity *entity, int layer)
{
  long				id;

  id = layer * 1000000000000;
  id += POSITION(entity)->y * 1000000;
  id += POSITION(entity)->x;
  this->go_.insert(std::pair<unsigned long, Entity*>(id, entity));
}

void				DrawCollection::remove(Entity *entity)
{
  // this->go_.remove(entity);
  (void)(entity);
}
