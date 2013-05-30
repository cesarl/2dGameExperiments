#include				"SceneMenu.hh"

// for test

int	g_x = 0;
int	g_y = 0;

SceneMenu::SceneMenu()
{}

SceneMenu::~SceneMenu()
{}

bool					SceneMenu::initialize()
{
  if (!this->room_.load("saves/", "chunk", g_x, g_y))
    {
      this->room_.generate();
      this->room_.save("saves/", "chunk", g_x, g_y);
    }
  if (!this->pnjmap_.load("saves/", "pnjmap", g_x, g_y))
    {
      this->pnjmap_.generate();
      this->pnjmap_.save("saves/", "pnjmap", g_x, g_y);
    }
  HEROS(&this->heros_);
  PISTOL(&this->heros_)->attachGridCollision(&this->grid_);
  MOVE(&this->heros_)->setMaxSpeed(4);
  POSITION(&this->heros_)->setPos(64 * 20 / 2 - 32, 64 * 10 / 2 - 32);
  this->room_.attachGrid(&this->grid_);
  this->pnjmap_.attachGrid(&this->grid_);
  return true;
}

void					SceneMenu::uninitialize()
{}


void					SceneMenu::update(ALLEGRO_EVENT *event)
{

  this->room_.update(event);
  this->pnjmap_.update(event);
  this->heros_.update();

  this->grid_.add(&this->heros_);
  this->room_.fillGrid();
  this->pnjmap_.fillGrid();
  this->grid_.update();
  this->grid_.clear();
  if (POSITION(&this->heros_)->x > 1300)
    {
      this->pnjmap_.save("saves/", "pnjmap", g_x, g_y);
      this->room_.save("saves/", "chunk", g_x, g_y);
      ++g_x;
      this->room_.clear();
      this->pnjmap_.clear();
      if (!this->pnjmap_.load("saves/", "pnjmap", g_x, g_y))
	{
	  this->pnjmap_.generate();
	  this->pnjmap_.save("saves/", "pnjmap", g_x, g_y);
	}
      if (!this->room_.load("saves/", "chunk", g_x, g_y))
	{
	  this->room_.generate();
	  this->room_.save("saves/", "chunk", g_x, g_y);
	}
      POSITION(&this->heros_)->x = 20;
    }
  if (POSITION(&this->heros_)->x < -20)
    {
      this->pnjmap_.save("saves/", "pnjmap", g_x, g_y);
      this->room_.save("saves/", "chunk", g_x, g_y);
      --g_x;
      this->room_.clear();
      this->pnjmap_.clear();
      if (!this->pnjmap_.load("saves/", "pnjmap", g_x, g_y))
	{
	  this->pnjmap_.generate();
	  this->pnjmap_.save("saves/", "pnjmap", g_x, g_y);
	}
      if (!this->room_.load("saves/", "chunk", g_x, g_y))
	{
	  this->room_.generate();
	  this->room_.save("saves/", "chunk", g_x, g_y);
	}
      POSITION(&this->heros_)->x = 1280;
    }
  if (POSITION(&this->heros_)->y < -20)
    {
      this->pnjmap_.save("saves/", "pnjmap", g_x, g_y);
      this->room_.save("saves/", "chunk", g_x, g_y);
      --g_y;
      this->room_.clear();
      this->pnjmap_.clear();
      if (!this->pnjmap_.load("saves/", "pnjmap", g_x, g_y))
	{
	  this->pnjmap_.generate();
	  this->pnjmap_.save("saves/", "pnjmap", g_x, g_y);
	}
      if (!this->room_.load("saves/", "chunk", g_x, g_y))
	{
	  this->room_.generate();
	  this->room_.save("saves/", "chunk", g_x, g_y);
	}
      POSITION(&this->heros_)->y = 640;
    }
  if (POSITION(&this->heros_)->y > 660)
    {
      this->pnjmap_.save("saves/", "pnjmap", g_x, g_y);
      this->room_.save("saves/", "chunk", g_x, g_y);
      ++g_y;
      this->room_.clear();
      this->pnjmap_.clear();
      if (!this->pnjmap_.load("saves/", "pnjmap", g_x, g_y))
	{
	  this->pnjmap_.generate();
	  this->pnjmap_.save("saves/", "pnjmap", g_x, g_y);
	}
      if (!this->room_.load("saves/", "chunk", g_x, g_y))
	{
	  this->room_.generate();
	  this->room_.save("saves/", "chunk", g_x, g_y);
	}
      POSITION(&this->heros_)->y = 20;
    }
  (void)(event);
}

void					SceneMenu::draw(ALLEGRO_EVENT *event)
{
  this->room_.draw(event);
  this->pnjmap_.draw(event);
  DrawManager::getInstance()->add(&this->heros_, 1);
  PISTOL(&heros_)->draw();
  (void)(event);
}

void					SceneMenu::input(ALLEGRO_EVENT *event)
{
  if (event->type == ALLEGRO_EVENT_KEY_DOWN && event->keyboard.keycode == ALLEGRO_KEY_P)
    this->pnjmap_.save("saves/", "pnjmap", g_x, g_y);
  (void)(event);
}

void					SceneMenu::receiveMessage(e_message type, bool activate)
{
  (void)type;
  (void)activate;
}
