#include				"SceneMainGame.hh"

SceneMainGame::SceneMainGame()
{
  ContentComponentImage			*backgroundImage;

  backgroundImage = new ContentComponentImage("assets/imgs/green_sky_background.jpg");
  this->background_.setContentComponent(backgroundImage);
  this->background_.setPos(0, 0);
}

SceneMainGame::~SceneMainGame()
{}

void					SceneMainGame::update(ALLEGRO_EVENT *event)
{
  // std::cout << "update" << std::endl;
  this->grid_.update();
  (void)(event);
}

void					SceneMainGame::draw(ALLEGRO_EVENT *event)
{
  // std::cout << "drae" << std::endl;
  this->background_.draw();
  this->grid_.draw();
  (void)(event);
}

void					SceneMainGame::input(ALLEGRO_EVENT *event)
{
  if (event->type == ALLEGRO_EVENT_KEY_DOWN)
    {
      if (event->keyboard.keycode == ALLEGRO_KEY_ESCAPE)
	{
	  this->messageSceneManager(MSG_ACTIVE, false, this->name_);
	  this->messageSceneManager(MSG_VISIBLE, false, this->name_);
	  this->messageSceneManager(MSG_ACTIVE, true, "menu");
	  this->messageSceneManager(MSG_VISIBLE, true, "menu");
	  this->grid_.newGame();
	}
      else
	this->grid_.input(event->keyboard.keycode);
    }
  (void)(event);
}
