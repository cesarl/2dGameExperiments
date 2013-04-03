#include				"SceneGameOver.hh"

SceneGameOver::SceneGameOver()
{
  ContentComponentText			*titleText;
  ContentComponentText			*playerNameText;
  ContentComponentText			*playerNameLabelText;
  ContentComponentText			*scoreText;
  ContentComponentText			*newTryText;
  ContentComponentText			*backToMenuText;

  this->selectedChoice_ = 0;

  titleText = new ContentComponentText("assets/fonts/LilitaOne-Regular.ttf", 80);
  titleText->setAlign(ALLEGRO_ALIGN_CENTER);
  titleText->setColor(al_map_rgb(255,100,100));
  *titleText = "GAME OVER";
  this->title_.setContentComponent(titleText);
  this->title_.setPos(500, 100);

  scoreText = new ContentComponentText("assets/fonts/LilitaOne-Regular.ttf", 50);
  scoreText->setAlign(ALLEGRO_ALIGN_CENTER);
  scoreText->setColor(al_map_rgb(40,200,100));
  *scoreText = "0";
  this->score_.setContentComponent(scoreText);
  this->score_.setPos(500, 200);

  playerNameLabelText = new ContentComponentText("assets/fonts/LilitaOne-Regular.ttf", 50);
  playerNameLabelText->setAlign(ALLEGRO_ALIGN_CENTER);
  playerNameLabelText->setColor(al_map_rgb(100,100,100));
  *playerNameLabelText = "Type your name";
  this->playerNameLabel_.setContentComponent(playerNameLabelText);
  this->playerNameLabel_.setPos(500, 300);

  playerNameText = new ContentComponentText("assets/fonts/LilitaOne-Regular.ttf", 50);
  playerNameText->setAlign(ALLEGRO_ALIGN_CENTER);
  playerNameText->setColor(al_map_rgb(15,200,250));
  *playerNameText = "";
  this->playerName_.setContentComponent(playerNameText);
  this->playerName_.setPos(500, 350);

  newTryText = new ContentComponentText("assets/fonts/LilitaOne-Regular.ttf", 50);
  newTryText->setAlign(ALLEGRO_ALIGN_CENTER);
  newTryText->setColor(al_map_rgb(50,100,100));
  *newTryText = "New Game";
  this->choices_[0].setContentComponent(newTryText);
  this->choices_[0].setPos(500, 450);

  backToMenuText = new ContentComponentText("assets/fonts/LilitaOne-Regular.ttf", 50);
  backToMenuText->setAlign(ALLEGRO_ALIGN_CENTER);
  backToMenuText->setColor(al_map_rgb(100,100,100));
  *backToMenuText = "Exit to menu";
  this->choices_[1].setContentComponent(backToMenuText);
  this->choices_[1].setPos(500, 600);
}

SceneGameOver::~SceneGameOver()
{}

void					SceneGameOver::update(ALLEGRO_EVENT *event)
{
  (void)(event);
}

void					SceneGameOver::draw(ALLEGRO_EVENT *event)
{
  int					i;

  this->title_.draw();
  this->score_.draw();
  this->playerNameLabel_.draw();
  this->playerName_.draw();
  i = 0;
  while (i < MAX_CHOICE_GO)
    this->choices_[i++].draw();
  (void)(event);
}

void					SceneGameOver::input(ALLEGRO_EVENT *event)
{
  if (event->type == ALLEGRO_EVENT_KEY_DOWN)
    {
      switch (event->keyboard.keycode)
	{
	case ALLEGRO_KEY_UP:
	  this->p_rollChoices(-1);
	  break;
	case ALLEGRO_KEY_DOWN:
	  this->p_rollChoices(1);
	  break;
	case ALLEGRO_KEY_SPACE:
	  this->sendMessage(MSG_ACTIVE, false, this->name_);
	  this->sendMessage(MSG_VISIBLE, false, this->name_);
	  this->p_saveScore();
	  if (this->selectedChoice_ == 0)
	    {
	      this->sendMessage(MSG_ACTIVE, true, "mainGame");
	      this->sendMessage(NEW_GAME, true, "mainGame");
	    }
	  else if (this->selectedChoice_ == 1)
	    {
	      this->sendMessage(MSG_ACTIVE, false, "mainGame");
	      this->sendMessage(MSG_VISIBLE, false, "mainGame");
	      this->sendMessage(MSG_ACTIVE, true, "menu");
	      this->sendMessage(MSG_VISIBLE, true, "menu");
	    }
	  break;
	}
    }
  this->playerName_.getContentComponent(TEXT_TYPE)->update(&(this->playerName_), event);
}

void					SceneGameOver::receiveMessage(e_message type, bool activate)
{
  (void)type;
  (void)activate;
}


// very dirty need to use template

void					SceneGameOver::receiveMessage(e_message type, void *data)
{
  std::ostringstream			o;
  int					*score;
  AContentComponent			*contentComponent;
  ContentComponentText			*text;

  if (type != SCORE)
    return;
  contentComponent = this->score_.getContentComponent(TEXT_TYPE);
  if (!contentComponent)
    return;
  text = dynamic_cast<ContentComponentText*>(contentComponent);
  score = (int*)(data);
  std::cout << *score << std::endl;
  o << *score;
  *text = o.str();
  (void)type;
  (void)data;
}

void					SceneGameOver::p_rollChoices(int direction)
{
  AContentComponent			*contentComponent;
  ContentComponentText			*textGameOver;

  contentComponent = this->choices_[this->selectedChoice_].getContentComponent(TEXT_TYPE);
  if (!contentComponent)
    return;
  textGameOver = dynamic_cast<ContentComponentText*>(contentComponent);
  textGameOver->setColor(al_map_rgb(100, 100, 100));
  this->selectedChoice_ += direction;
  if (this->selectedChoice_ >= MAX_CHOICE_GO)
    this->selectedChoice_ = 0;
  else if (this->selectedChoice_ < 0)
    this->selectedChoice_ = MAX_CHOICE_GO - 1;
  contentComponent = this->choices_[this->selectedChoice_].getContentComponent(TEXT_TYPE);
  if (!contentComponent)
    return;
  textGameOver = dynamic_cast<ContentComponentText*>(contentComponent);
  textGameOver->setColor(al_map_rgb(30, 100, 100));
}

void					SceneGameOver::p_saveScore()
{
  int					score;
  std::stringstream			tmp;

  tmp << dynamic_cast<ContentComponentText*>(this->score_.getContentComponent(TEXT_TYPE))->getText();
  tmp >> score;
  SaveManager::getInstance()->
    save(
	 dynamic_cast<ContentComponentText*>(this->playerName_.getContentComponent(TEXT_TYPE))->getText(),
	 score);
}
