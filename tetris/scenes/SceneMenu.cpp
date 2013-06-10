#include				"SceneMenu.hh"

Entity					*MenuGui::particules_;

SceneMenu::SceneMenu()
{
}

SceneMenu::~SceneMenu()
{}

void					SceneMenu::update(ALLEGRO_EVENT *event)
{
  MenuGui::particules_->update();
  (void)(event);
}

void					SceneMenu::draw(ALLEGRO_EVENT *event)
{
  this->background_.draw();
  MenuGui::particules_->draw();
  this->title_.draw();
  this->gui_.draw();
  (void)(event);
}

void					SceneMenu::input(ALLEGRO_EVENT *event)
{
  this->gui_.event(event);
  (void)(event);
}

void					SceneMenu::receiveMessage(e_message type, bool activate)
{
  (void)type;
  (void)activate;
}

bool					SceneMenu::initialize()
{
  IMAGE(&(this->background_))->setBitmap("assets/imgs/main-bg.jpg");
  POSITION(&(this->background_))->setPos(0, 0);

  TEXT(&(this->title_))->setFont("assets/fonts/LilitaOne-Regular.ttf", 80);
  TEXT(&(this->title_))->align = ALLEGRO_ALIGN_CENTER;
  *TEXT(&(this->title_)) = "TETRIS";
  POSITION(&(this->title_))->setPos(500, 150);

  MenuGui::particules_ = new Entity;
  if (!MenuGui::particules_)
    return false;
  POSITION(MenuGui::particules_)->setPos(250, 320);
  PARTICULE_EMITTER(MenuGui::particules_)->config(
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

  std::string				text[] = {"New Game", "Scores", "Exit"};
  GuiSelectableText			*t;

  this->gui_.setPosition(Vector3d(0, 0, 0));
  for (int i = 0; i < 3; ++i)
    {
      t = new GuiSelectableText;
      if (!t)
	return false;
      t->setPosition(Vector3d(500, 300 + 150 * i, 0));
      t->setupText(text[i], FontManager::getInstance()->load("assets/fonts/LilitaOne-Regular.ttf", 50));
      t->setSelectAction(&MenuGui::selectMenuItem);
      t->setUnselectAction(&MenuGui::unselectMenuItem);
      switch (i)
	{
	case 0:
	  t->setPressAction(&MenuGui::pressNewGameMenuItem);
	  break;
	case 1:
	  t->setPressAction(&MenuGui::pressScoreMenuItem);
	  break;
	case 2:
	  t->setPressAction(&MenuGui::pressExitMenuItem);
	  break;
	default:
	  break;
	}
      this->gui_.pushComponent(t);
    }
  return true;
}

void					SceneMenu::uninitialize()
{
  delete MenuGui::particules_;
}

void					MenuGui::selectMenuItem(GuiComponent *c)
{
  GuiSelectableText			*t = dynamic_cast<GuiSelectableText*>(c);

  t->getText()->setColor(al_map_rgb(255, 0, 255));
  POSITION(MenuGui::particules_)->setPos(250, t->getPosition().getY() + 20);
}

void					MenuGui::unselectMenuItem(GuiComponent *c)
{
  GuiSelectableText			*t = dynamic_cast<GuiSelectableText*>(c);

  t->getText()->setColor(al_map_rgb(125, 125, 125));
}

void					MenuGui::pressExitMenuItem(GuiComponent *c)
{
  EventManager::getInstance()->stop();
  (void)c;
}

void					MenuGui::pressNewGameMenuItem(GuiComponent *c)
{
  SceneManager::getInstance()->handleMessage(MSG_ACTIVE, false, "menu");
  SceneManager::getInstance()->handleMessage(MSG_VISIBLE, false, "menu");
  SceneManager::getInstance()->handleMessage(MSG_ACTIVE, true, "mainGame");
  SceneManager::getInstance()->handleMessage(MSG_VISIBLE, true, "mainGame");
  SceneManager::getInstance()->handleMessage(NEW_GAME, true, "mainGame");
  (void)c;
}

void					MenuGui::pressScoreMenuItem(GuiComponent *c)
{
  (void)c;
}
