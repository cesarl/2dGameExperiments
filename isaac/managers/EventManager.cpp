#include				"EventManager.hh"

EventManager::EventManager() :
  event_queue_(NULL),
  timer_(NULL),
  sceneManager_(NULL),
  pause_(true)
{
}

EventManager::~EventManager()
{
}

bool					EventManager::initialize()
{
  if (!al_install_keyboard())
    return false;
  if (!al_install_mouse())
    return false;
  this->event_queue_ = al_create_event_queue();
  if (!this->event_queue_)
    return false;
  this->timer_ = al_create_timer(1.0 / 60);
  if (!this->timer_)
    return false;

  al_register_event_source(this->event_queue_, al_get_keyboard_event_source());
  al_register_event_source(this->event_queue_, al_get_mouse_event_source());
  al_register_event_source(this->event_queue_, al_get_display_event_source(al_get_current_display()));
  al_register_event_source(this->event_queue_, al_get_timer_event_source(this->timer_));
  al_start_timer(this->timer_);

  this->sceneManager_ = SceneManager::getInstance();
  return true;
}

void					EventManager::uninitialize()
{
  if (this->event_queue_)
    al_destroy_event_queue(this->event_queue_);
  if (this->timer_)
    al_destroy_timer(this->timer_);
  al_uninstall_keyboard();
  al_uninstall_mouse();
}


void					EventManager::play()
{
  bool					draw;
  t_iter				it;

  if (!this->sceneManager_)
    {
      std::cerr << "Error : Event Manager - SceneManager has not been linked" << std::endl;
      return;
    }
  this->pause_ = false;
  while (!this->pause_)
    {
      ALLEGRO_EVENT			 ev;
      draw = false;
      al_wait_for_event(this->event_queue_, &ev);
      if (ev.type == ALLEGRO_EVENT_TIMER)
	{
	  draw = true;
	  this->sceneManager_->updateEvent(&ev);
	}
      else
	this->sceneManager_->inputEvent(&ev);
      if (draw && al_is_event_queue_empty(this->event_queue_))
	{
	  this->sceneManager_->drawEvent(&ev);
	  DrawManager::getInstance()->draw();
	}
      if (ev.type == ALLEGRO_EVENT_KEY_DOWN || ev.type == ALLEGRO_EVENT_KEY_UP)
	{
	  it = this->inputSubscribeList_.begin();
	  while (it != this->inputSubscribeList_.end())
	    {
	      (*it)->inputEvent(&ev);
	      ++it;
	    }
	}
    }
}

void					EventManager::pause()
{
  this->pause_ = true;
}

EventManager				*EventManager::getInstance()
{
  static EventManager			that;
  return &that;
}

void					EventManager::inputSubscribe(Input *input)
{
  this->inputSubscribeList_.push_back(input);
}

void					EventManager::inputUnsubscribe(Input *input)
{
  std::remove(this->inputSubscribeList_.begin(), this->inputSubscribeList_.end(), input);
}
