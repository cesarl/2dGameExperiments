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
  // std::cout << "update" << std::endl;
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
	  this->messageSceneManager(MSG_ACTIVE, false, this->name_);
	  this->messageSceneManager(MSG_VISIBLE, false, this->name_);
	  break;
	}
    }
  (void)(event);
}

void					SceneMenu::p_rollMenu(int direction)
{
  ContentComponentText			*textMenu;

  textMenu = dynamic_cast<ContentComponentText*>(this->choices_[this->selectedChoice_].getContentComponent());
  textMenu->setColor(al_map_rgb(100, 100, 100));
  this->selectedChoice_ += direction;
  if (this->selectedChoice_ >= MAX_CHOICE)
    this->selectedChoice_ = 0;
  else if (this->selectedChoice_ < 0)
    this->selectedChoice_ = MAX_CHOICE - 1;
  textMenu = dynamic_cast<ContentComponentText*>(this->choices_[this->selectedChoice_].getContentComponent());
  textMenu->setColor(al_map_rgb(30, 100, 100));
}
