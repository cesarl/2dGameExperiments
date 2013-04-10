#include				"ScenePause.hh"

ScenePause::ScenePause()
{
  this->selectedChoice_ = 0;

  TEXT(&(this->choices_[0]))->setFont("assets/fonts/LilitaOne-Regular.ttf", 50);
  TEXT(&(this->choices_[0]))->align = ALLEGRO_ALIGN_CENTER;
  TEXT(&(this->choices_[0]))->color = al_map_rgb(50,100,100);
  *TEXT(&(this->choices_[0])) = "Back to Game";
  POSITION(&(this->choices_[0]))->setPos(374, 300);

  TEXT(&(this->choices_[1]))->setFont("assets/fonts/LilitaOne-Regular.ttf", 50);
  TEXT(&(this->choices_[1]))->align = ALLEGRO_ALIGN_CENTER;
  TEXT(&(this->choices_[1]))->color = al_map_rgb(100,100,100);
  *TEXT(&(this->choices_[1])) = "New Game";
  POSITION(&(this->choices_[1]))->setPos(374, 450);

  TEXT(&(this->choices_[2]))->setFont("assets/fonts/LilitaOne-Regular.ttf", 50);
  TEXT(&(this->choices_[2]))->align = ALLEGRO_ALIGN_CENTER;
  TEXT(&(this->choices_[2]))->color = al_map_rgb(100,100,100);
  *TEXT(&(this->choices_[2])) = "Exit to menu";
  POSITION(&(this->choices_[2]))->setPos(374, 600);
}

ScenePause::~ScenePause()
{}

void					ScenePause::update(ALLEGRO_EVENT *event)
{
  (void)(event);
}

void					ScenePause::draw(ALLEGRO_EVENT *event)
{
  int					i;

  this->background_.draw();
  this->title_.draw();
  i = 0;
  while (i < MAX_CHOICE)
    this->choices_[i++].draw();
  (void)(event);
}

void					ScenePause::input(ALLEGRO_EVENT *event)
{
  if (event->type == ALLEGRO_EVENT_KEY_DOWN)
    {
      switch (event->keyboard.keycode)
	{
	case ALLEGRO_KEY_UP:
	  this->p_rollPause(-1);
	  break;
	case ALLEGRO_KEY_DOWN:
	  this->p_rollPause(1);
	  break;
	case ALLEGRO_KEY_ENTER:
	  this->sendMessage(MSG_ACTIVE, false, this->name_);
	  this->sendMessage(MSG_VISIBLE, false, this->name_);
	  if (this->selectedChoice_ == 0)
	    {
	      this->sendMessage(MSG_ACTIVE, true, "mainGame");
	    }
	  else if (this->selectedChoice_ == 1)
	    {
	      this->sendMessage(MSG_ACTIVE, true, "mainGame");
	      this->sendMessage(NEW_GAME, true, "mainGame");
	    }
	  else if (this->selectedChoice_ == 2)
	    {
	      this->sendMessage(MSG_ACTIVE, false, "mainGame");
	      this->sendMessage(MSG_VISIBLE, false, "mainGame");
	      this->sendMessage(MSG_ACTIVE, true, "menu");
	      this->sendMessage(MSG_VISIBLE, true, "menu");
	    }
	  break;
	}
    }
  (void)(event);
}

void					ScenePause::receiveMessage(e_message type, bool activate)
{
  (void)type;
  (void)activate;
}

void					ScenePause::receiveMessage(e_message type, void *data)
{
  (void)type;
  (void)data;
}

void					ScenePause::p_rollPause(int direction)
{

  TEXT(&(this->choices_[this->selectedChoice_]))->color = al_map_rgb(100, 100, 100);
  this->selectedChoice_ += direction;
  if (this->selectedChoice_ >= MAX_CHOICE)
    this->selectedChoice_ = 0;
  else if (this->selectedChoice_ < 0)
    this->selectedChoice_ = MAX_CHOICE - 1;
  TEXT(&(this->choices_[this->selectedChoice_]))->color = al_map_rgb(30, 100, 100);
}
