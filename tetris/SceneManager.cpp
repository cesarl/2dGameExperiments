#include				"SceneManager.hh"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

void					SceneManager::add(AScene * scene, int priority)
{
  t_iter				i;

  i = this->collection_.begin();
  while (i != this->collection_.end())
    {
      if (priority <= (*i)->getPriority())
	break;
      ++i;
    }
  if (i != this->collection_.end())
    this->collection_.insert(i, scene);
  else
    this->collection_.push_back(scene);
  scene->setPriority(priority);
}

AScene					*SceneManager::remove(AScene * scene)
{
  t_iter				i;
  AScene				*res;

  i = std::find(this->collection_.begin(), this->collection_.end(), scene);
  if (i != this->collection_.end())
    {
      res = *i;
      this->collection_.erase(i);
      return res;
    }
  return NULL;
}

void					SceneManager::setVisibleAll(bool val)
{
  t_iter				i;

  i = this->collection_.begin();
  while (i != this->collection_.end())
    {
      (*i)->setVisible(val);
      ++i;
    }
}
void					SceneManager::setActiveAll(bool val)
{
  t_iter				i;

  i = this->collection_.begin();
  while (i != this->collection_.end())
    {
      (*i)->setActive(val);
      ++i;
    }
}

void					SceneManager::setPriority(AScene *scene, int priority)
{
  (void)(scene);
  (void)(priority);
}

void					SceneManager::updateEvent(ALLEGRO_EVENT *event)
{
  t_iter				i;

  i = this->collection_.begin();
  while (i != this->collection_.end())
    {
      if ((*i)->getActive())
	(*i)->update(event);
      ++i;
    }
}

void					SceneManager::drawEvent(ALLEGRO_EVENT *event)
{
  t_iter				i;

  i = this->collection_.begin();
  while (i != this->collection_.end())
    {
      if ((*i)->getVisible())
	(*i)->update(event);
      ++i;
    }
}

void					SceneManager::inputEvent(ALLEGRO_EVENT *event)
{
  t_iter				i;

  i = this->collection_.begin();
  while (i != this->collection_.end())
    {
      if ((*i)->getActive())
	(*i)->input(event);
      ++i;
    }
}
