#include				"SceneMenu.hh"

SceneMenu::SceneMenu()
{
  ContentComponentImage			*backgroundImage;
  ContentComponentText			*titleText;
  ContentComponentText			*newGameText;
  ContentComponentText			*scoreText;
  ContentComponentText			*exitText;

  backgroundImage = new ContentComponentImage("assets/imgs/blue_sky_background.jpg");
  this->background_.setContentComponent(backgroundImage);
  this->background_.setPos(0, 0);

  titleText = new ContentComponentText("assets/fonts/LilitaOne-Regular.ttf", 80);
  titleText->setAlign(ALLEGRO_ALIGN_CENTER);
  *titleText = "TETRIS";
  this->title_.setContentComponent(titleText);
  this->title_.setPos(374, 150);

  this->selectedChoice_ = 0;

  newGameText = new ContentComponentText("assets/fonts/LilitaOne-Regular.ttf", 50);
  newGameText->setAlign(ALLEGRO_ALIGN_CENTER);
  newGameText->setColor(al_map_rgb(50,100,100));
  *newGameText = "New Game";
  this->choices_[0].setContentComponent(newGameText);
  this->choices_[0].setPos(374, 300);

  scoreText = new ContentComponentText("assets/fonts/LilitaOne-Regular.ttf", 50);
  scoreText->setAlign(ALLEGRO_ALIGN_CENTER);
  scoreText->setColor(al_map_rgb(100,100,100));
  *scoreText = "Scores";
  this->choices_[1].setContentComponent(scoreText);
  this->choices_[1].setPos(374, 450);

  exitText = new ContentComponentText("assets/fonts/LilitaOne-Regular.ttf", 50);
  exitText->setAlign(ALLEGRO_ALIGN_CENTER);
  exitText->setColor(al_map_rgb(100,100,100));
  *exitText = "Exit";
  this->choices_[2].setContentComponent(exitText);
  this->choices_[2].setPos(374, 600);
}

SceneMenu::~SceneMenu()
{}

void					SceneMenu::update(ALLEGRO_EVENT *event)
{
  (void)(event);
}

void					SceneMenu::draw(ALLEGRO_EVENT *event)
{
  int					i;

  this->background_.draw();
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
	case ALLEGRO_KEY_SPACE:
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
  AContentComponent			*contentComponent;
  ContentComponentText			*textMenu;

  contentComponent = this->choices_[this->selectedChoice_].getContentComponent(TEXT_TYPE);
  if (!contentComponent)
    return;
  textMenu = dynamic_cast<ContentComponentText*>(contentComponent);
  textMenu->setColor(al_map_rgb(100, 100, 100));
  this->selectedChoice_ += direction;
  if (this->selectedChoice_ >= MAX_CHOICE)
    this->selectedChoice_ = 0;
  else if (this->selectedChoice_ < 0)
    this->selectedChoice_ = MAX_CHOICE - 1;
  contentComponent = this->choices_[this->selectedChoice_].getContentComponent(TEXT_TYPE);
  if (!contentComponent)
    return;
  textMenu = dynamic_cast<ContentComponentText*>(contentComponent);
  textMenu->setColor(al_map_rgb(30, 100, 100));
}
