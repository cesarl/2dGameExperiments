#include			"DrawManager.hh"

DrawManager::DrawManager()
{
}

DrawManager::~DrawManager()
{
  this->clear();
}

DrawManager			*DrawManager::getInstance()
{
  static DrawManager		that;

  return &that;
}

void				DrawManager::clear()
{
  this->go_.clear();
}


void				DrawManager::draw(ALLEGRO_EVENT *event)
{
  std::multimap<unsigned long, Entity*>::iterator it;

  it = this->go_.begin();
  al_clear_to_color(al_map_rgb(200, 200, 200));
  while (it != this->go_.end())
    {
      it->second->draw();
      ++it;
    }
  this->go_.clear();
  al_flip_display();
  (void)event;
}

void				DrawManager::add(Entity *entity, int layer)
{
  long				id;

  id = layer * 1000000000000;
  id += POSITION(entity)->y * 1000000;
  id += POSITION(entity)->x;
  this->go_.insert(std::pair<unsigned long, Entity*>(id, entity));
}
