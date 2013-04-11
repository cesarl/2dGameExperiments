#include				"SceneMenu.hh"

SceneMenu::SceneMenu()
{
  this->selectedChoice_ = 0;

  IMAGE(&(this->background_))->setBitmap("assets/imgs/main-bg.jpg");
  POSITION(&(this->background_))->setPos(0, 0);

  TEXT(&(this->title_))->setFont("assets/fonts/LilitaOne-Regular.ttf", 80);
  TEXT(&(this->title_))->align = ALLEGRO_ALIGN_CENTER;
  *TEXT(&(this->title_)) = "TETRIS";
  POSITION(&(this->title_))->setPos(500, 150);

  TEXT(&(this->choices_[0]))->setFont("assets/fonts/LilitaOne-Regular.ttf", 50);
  TEXT(&(this->choices_[0]))->align = ALLEGRO_ALIGN_CENTER;
  TEXT(&(this->choices_[0]))->color = al_map_rgb(50,100,100);
  *TEXT(&(this->choices_[0])) = "New Game";
  POSITION(&(this->choices_[0]))->setPos(500, 300);

  TEXT(&(this->choices_[1]))->setFont("assets/fonts/LilitaOne-Regular.ttf", 50);
  TEXT(&(this->choices_[1]))->align = ALLEGRO_ALIGN_CENTER;
  TEXT(&(this->choices_[1]))->color = al_map_rgb(100,100,100);
  *TEXT(&(this->choices_[1])) = "Scores";
  POSITION(&(this->choices_[1]))->setPos(500, 450);

  TEXT(&(this->choices_[2]))->setFont("assets/fonts/LilitaOne-Regular.ttf", 50);
  TEXT(&(this->choices_[2]))->align = ALLEGRO_ALIGN_CENTER;
  TEXT(&(this->choices_[2]))->color = al_map_rgb(100,100,100);
  *TEXT(&(this->choices_[2])) = "Exit";
  POSITION(&(this->choices_[2]))->setPos(500, 600);

  POSITION(&(this->particules_))->setPos(250, 320);
  PARTICULE_EMITTER(&(this->particules_))->config(
						  "assets/imgs/stars.png",
						  10,
						  10,
						  10,
						  5,
						  10,
						  0.05,
						  250,
						  500,
						  50
						  );
}

SceneMenu::~SceneMenu()
{}

void					SceneMenu::update(ALLEGRO_EVENT *event)
{
  this->particules_.update();
  (void)(event);
}

void					SceneMenu::draw(ALLEGRO_EVENT *event)
{
  int					i;

  this->background_.draw();
  this->particules_.draw();
  this->title_.draw();
  i = 0;
  while (i < MAX_CHOICE)
    this->choices_[i++].draw();
  (void)(event);
}

void					SceneMenu::input(ALLEGRO_EVENT *event)
{
  if (event->type == ALLEGRO_EVENT_KEY_DOWN)
    {
      switch (event->keyboard.keycode)
	{
	case ALLEGRO_KEY_UP:
	  this->p_rollMenu(-1);
	  break;
	case ALLEGRO_KEY_DOWN:
	  this->p_rollMenu(1);
	  break;
	case ALLEGRO_KEY_ENTER:
	  if (this->selectedChoice_ == 2)
	    {
	      this->sendMessage(MSG_ACTIVE, false, this->name_);
	      this->sendMessage(MSG_VISIBLE, false, this->name_);
	      this->sendMessage(MSG_EXITAPP, false, "");
	    }
	  else if (this->selectedChoice_ == 0)
	    {
	      this->sendMessage(MSG_ACTIVE, false, this->name_);
	      this->sendMessage(MSG_VISIBLE, false, this->name_);
	      this->sendMessage(MSG_ACTIVE, true, "mainGame");
	      this->sendMessage(MSG_VISIBLE, true, "mainGame");
	      this->sendMessage(NEW_GAME, true, "mainGame");
	    }
	  break;
	}
    }
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

void					SceneMenu::p_rollMenu(int direction)
{
  TEXT(&(this->choices_[this->selectedChoice_]))->color = al_map_rgb(100, 100, 100);
  this->selectedChoice_ += direction;
  if (this->selectedChoice_ >= MAX_CHOICE)
    this->selectedChoice_ = 0;
  else if (this->selectedChoice_ < 0)
    this->selectedChoice_ = MAX_CHOICE - 1;
  TEXT(&(this->choices_[this->selectedChoice_]))->color = al_map_rgb(30, 100, 100);
  POSITION(&(this->particules_))->setPos(250, POSITION( &(this->choices_[this->selectedChoice_]))->y + 20);
}
