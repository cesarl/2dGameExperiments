#include				"SceneGameOver.hh"

SceneGameOver::SceneGameOver()
{
  this->selectedChoice_ = 0;

  TEXT(&(this->title_))->setFont("assets/fonts/LilitaOne-Regular.ttf", 80);
  TEXT(&(this->title_))->align = ALLEGRO_ALIGN_CENTER;
  TEXT(&(this->title_))->color = al_map_rgb(255,100,100);
  *TEXT(&(this->title_)) = "GAME OVER";
  POSITION(&(this->title_))->setPos(500, 150);

  TEXT(&(this->score_))->setFont("assets/fonts/LilitaOne-Regular.ttf", 50);
  TEXT(&(this->score_))->align = ALLEGRO_ALIGN_CENTER;
  TEXT(&(this->score_))->color = al_map_rgb(40,200,100);
  *TEXT(&(this->score_)) = "0";
  POSITION(&(this->score_))->setPos(500, 200);

  TEXT(&(this->playerNameLabel_))->setFont("assets/fonts/LilitaOne-Regular.ttf", 50);
  TEXT(&(this->playerNameLabel_))->align = ALLEGRO_ALIGN_CENTER;
  TEXT(&(this->playerNameLabel_))->color = al_map_rgb(100, 100, 100);
  *TEXT(&(this->playerNameLabel_)) = "Type your name";
  POSITION(&(this->playerNameLabel_))->setPos(500, 300);

  TEXT(&(this->playerName_))->setFont("assets/fonts/LilitaOne-Regular.ttf", 50);
  TEXT(&(this->playerName_))->align = ALLEGRO_ALIGN_CENTER;
  TEXT(&(this->playerName_))->color = al_map_rgb(15, 200, 250);
  *TEXT(&(this->playerName_)) = "";
  POSITION(&(this->playerName_))->setPos(500, 350);
  TEXT_INPUT(&(this->playerName_));

  TEXT(&(this->choices_[0]))->setFont("assets/fonts/LilitaOne-Regular.ttf", 50);
  TEXT(&(this->choices_[0]))->align = ALLEGRO_ALIGN_CENTER;
  TEXT(&(this->choices_[0]))->color = al_map_rgb(50,100,100);
  *TEXT(&(this->choices_[0])) = "New Game";
  POSITION(&(this->choices_[0]))->setPos(500, 450);

  TEXT(&(this->choices_[1]))->setFont("assets/fonts/LilitaOne-Regular.ttf", 50);
  TEXT(&(this->choices_[1]))->align = ALLEGRO_ALIGN_CENTER;
  TEXT(&(this->choices_[1]))->color = al_map_rgb(100,100,100);
  *TEXT(&(this->choices_[1])) = "Exit to menu";
  POSITION(&(this->choices_[1]))->setPos(500, 600);
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
	case ALLEGRO_KEY_ENTER:
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
  TEXT_INPUT(&(this->playerName_))->input(event);
  // this->playerName_.getContentComponent(TEXT_TYPE)->update(&(this->playerName_), event);
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

  if (type != SCORE)
    return;
  score = (int*)(data);
  std::cout << *score << std::endl;
  o << *score;
  *TEXT(&(this->score_)) = o.str();
  (void)type;
  (void)data;
}

void					SceneGameOver::p_rollChoices(int direction)
{
  TEXT(&(this->choices_[this->selectedChoice_]))->color = al_map_rgb(100, 100, 100);
  this->selectedChoice_ += direction;
  if (this->selectedChoice_ >= MAX_CHOICE_GO)
    this->selectedChoice_ = 0;
  else if (this->selectedChoice_ < 0)
    this->selectedChoice_ = MAX_CHOICE_GO - 1;
  TEXT(&(this->choices_[this->selectedChoice_]))->color = al_map_rgb(30, 100, 100);
}

void					SceneGameOver::p_saveScore()
{
  int					score;
  std::stringstream			tmp;

  tmp << TEXT(&(this->score_))->text;
  tmp >> score;
  SaveManager::getInstance()->save(TEXT(&(this->playerName_))->text, score);
}
