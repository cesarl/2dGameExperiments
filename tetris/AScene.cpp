#include				"AScene.hh"

AScene::AScene(std::string const & name, bool active, bool visible) :
  name_(name), active_(active), visible_(visible), display_(NULL), sceneManager_(NULL)
{}

AScene::~AScene()
{}

std::string const &			AScene::getName() const
{
  return this->name_;
}

bool					AScene::getActive() const
{
  return this->active_;
}

bool					AScene::getVisible() const
{
  return this->visible_;
}

int					AScene::getPriority() const
{
  return this->priority_;
}

void					AScene::setName(std::string const name)
{
  this->name_ = name;
}

void					AScene::setActive(bool active)
{
  this->active_ = active;
}

void					AScene::setVisible(bool visible)
{
  this->visible_ = visible;
}

void					AScene::setPriority(int priority)
{
  this->priority_ = priority;
}

void					AScene::setDisplay(ALLEGRO_DISPLAY *display)
{
  this->display_ = display;
}

void					AScene::setManager(SceneManager *manager)
{
  this->sceneManager_ = manager;
}

// Send a message to SceneManager
// Examples :
// messageSceneManager(ACTIVE, false, "");
// --> set all scene active_ to false
// messageSceneManager(DISPLAY, true, "CREDIT");
// --> set scene with title CREDIT display to true

void					AScene::messageSceneManager(int type, bool activate, std::string const & sceneName)
{
  AScene				*tmp;

  switch (type)
    {
    case MSG_ACTIVE:
      if (sceneName.empty())
	this->sceneManager_->setActiveAll(activate);
      else
	{
	  tmp = this->sceneManager_->get(sceneName);
	  if (tmp)
	    tmp->setActive(activate);
	  else
	    std::cout << "existe pas " << sceneName << std::endl;
	}
      break;
    case MSG_VISIBLE:
      if (sceneName.empty())
	this->sceneManager_->setVisibleAll(activate);
      else
	{
	  tmp = this->sceneManager_->get(sceneName);
	  if (tmp)
	    tmp->setVisible(activate);
	}
      break;
    case MSG_EXITAPP:
      this->sceneManager_->exit();
      break;
    }
}
