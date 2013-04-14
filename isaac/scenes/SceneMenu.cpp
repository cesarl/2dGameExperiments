#include				"SceneMenu.hh"

SceneMenu::SceneMenu()
{
  if (!this->room_.load("saves/", "chunk", 0, 0))
    {
      this->room_.generate();
      this->room_.save("saves/", "chunk", 0, 0);
    }
  if (!this->pnjmap_.load("saves/", "pnjmap", 0, 0))
    {
      this->pnjmap_.generate();
      // this->pnjmap_.save("saves/", "pnjmap", 0, 0);
    }
  HEROS(&this->heros_);
  POSITION(&this->heros_)->setPos(64 * 20 / 2 - 32, 64 * 10 / 2 - 32);
}

SceneMenu::~SceneMenu()
{}

void					SceneMenu::update(ALLEGRO_EVENT *event)
{
  std::vector<Entity*>			*boundlist;
  std::vector<Entity*>::iterator	it;

  this->room_.update(event);
  this->pnjmap_.update(event);
  this->heros_.update();

  boundlist = this->pnjmap_.getSelection(&this->heros_);
  it = boundlist->begin();
  if (!boundlist->empty())
    POSITION(&this->heros_)->reversePos();
  while (it != boundlist->end())
    {
      FORCE_RESISTANCE(&this->heros_)->applyForce(*it);
      ++it;
    }

  boundlist = this->room_.getSelection(&this->heros_);
  it = boundlist->begin();
  if (!boundlist->empty())
    POSITION(&this->heros_)->reversePos();
  while (it != boundlist->end())
    {
      FORCE_RESISTANCE(&this->heros_)->applyForce(*it);
      ++it;
    }
  (void)(event);
}

void					SceneMenu::draw(ALLEGRO_EVENT *event)
{
  this->room_.draw(event);
  this->pnjmap_.draw(event);
  this->heros_.draw();
  (void)(event);
}

void					SceneMenu::input(ALLEGRO_EVENT *event)
{
  (void)(event);
}

void					SceneMenu::receiveMessage(e_message type, bool activate)
{
  (void)type;
  (void)activate;
}

void					SceneMenu::receiveMessage(e_message type, void *data)
{
  (void)type;
  (void)data;
}
