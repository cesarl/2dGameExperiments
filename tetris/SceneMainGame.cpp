#include				"SceneMainGame.hh"

SceneMainGame::SceneMainGame()
{
  ContentComponentImage			*backgroundImage;
  ContentComponentImage			*bigBackgroundImage;

  bigBackgroundImage = new ContentComponentImage("assets/imgs/main-bg.jpg");
  this->background_.setContentComponent(bigBackgroundImage);
  this->background_.setPos(0, 0);

  backgroundImage = new ContentComponentImage("assets/imgs/green_sky_background.jpg");
  this->background_.setContentComponent(backgroundImage);
  this->background_.setPos(0, 0);
}

SceneMainGame::~SceneMainGame()
{}

void					SceneMainGame::update(ALLEGRO_EVENT *event)
{
  this->grid_.update();
  if (this->grid_.getGameOver())
    {
      this->sendMessage(SCORE, &(this->score_), "gameOver");
      this->sendMessage(MSG_ACTIVE, false, this->name_);
      this->sendMessage(MSG_ACTIVE, true, "gameOver");
      this->sendMessage(MSG_VISIBLE, true, "gameOver");
    }
  // std::cout << this->score_ << std::endl;
  (void)(event);
}

void					SceneMainGame::draw(ALLEGRO_EVENT *event)
{
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
	  this->sendMessage(MSG_ACTIVE, false, this->name_);
	  this->sendMessage(MSG_ACTIVE, true, "pause");
	  this->sendMessage(MSG_VISIBLE, true, "pause");
	}
      else
	this->grid_.input(event->keyboard.keycode);
    }
  (void)(event);
}

void					SceneMainGame::receiveMessage(e_message type, bool activate)
{
  if (type == NEW_GAME)
    {
      this->grid_.newGame(&(this->score_));
    }
  (void)type;
  (void)activate;
}

void					SceneMainGame::receiveMessage(e_message type, void *data)
{
  (void)type;
  (void)data;
}
