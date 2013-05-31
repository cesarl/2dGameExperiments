#include				"Input.hh"
#include				"EventManager.hh"

#include				<iostream> //pour le debug - a virer

Input::Input(Entity *entity) : AComponent(entity, T_INPUT)
{
  this->up = false;
  this->down = false;
  this->left = false;
  this->right = false;
  this->space = false;
  this->sup = false;
  this->sdown = false;
  this->sleft = false;
  this->sright = false;
}

Input::~Input()
{
  EventManager::getInstance()->inputUnsubscribe(this);
}

void					Input::update(double time)
{
  (void)(time);
}

void					Input::draw()
{}

void					Input::inputEvent(ALLEGRO_EVENT * event)
{
  switch (event->keyboard.keycode)
    {
    case ALLEGRO_KEY_UP:
      if (event->type == ALLEGRO_EVENT_KEY_DOWN)
	this->up = true;
      else if (event->type == ALLEGRO_EVENT_KEY_UP)
	this->up = false;
      break;
    case ALLEGRO_KEY_DOWN:
      if (event->type == ALLEGRO_EVENT_KEY_DOWN)
	this->down = true;
      else if (event->type == ALLEGRO_EVENT_KEY_UP)
	this->down = false;
      break;
    case ALLEGRO_KEY_LEFT:
      if (event->type == ALLEGRO_EVENT_KEY_DOWN)
	this->left = true;
      else if (event->type == ALLEGRO_EVENT_KEY_UP)
	this->left = false;
      break;
    case ALLEGRO_KEY_RIGHT:
      if (event->type == ALLEGRO_EVENT_KEY_DOWN)
	this->right = true;
      else if (event->type == ALLEGRO_EVENT_KEY_UP)
	this->right = false;
      break;
    case ALLEGRO_KEY_W:
      if (event->type == ALLEGRO_EVENT_KEY_DOWN)
	this->sup = true;
      else if (event->type == ALLEGRO_EVENT_KEY_UP)
	this->sup = false;
      break;
    case ALLEGRO_KEY_S:
      if (event->type == ALLEGRO_EVENT_KEY_DOWN)
	this->sdown = true;
      else if (event->type == ALLEGRO_EVENT_KEY_UP)
	this->sdown = false;
      break;
    case ALLEGRO_KEY_A:
      if (event->type == ALLEGRO_EVENT_KEY_DOWN)
	this->sleft = true;
      else if (event->type == ALLEGRO_EVENT_KEY_UP)
	this->sleft = false;
      break;
    case ALLEGRO_KEY_D:
      if (event->type == ALLEGRO_EVENT_KEY_DOWN)
	this->sright = true;
      else if (event->type == ALLEGRO_EVENT_KEY_UP)
	this->sright = false;
      break;
    case ALLEGRO_KEY_SPACE:
      if (event->type == ALLEGRO_EVENT_KEY_DOWN)
	this->space = true;
      else if (event->type == ALLEGRO_EVENT_KEY_UP)
	this->space = false;
      break;
    }
}

void					Input::listen(bool value)
{
  if (value)
    {
      EventManager::getInstance()->inputSubscribe(this);
    }
  else
    {
      EventManager::getInstance()->inputUnsubscribe(this);
      this->up = false;
      this->down = false;
      this->left = false;
      this->right = false;
      this->space = false;
      this->sup = false;
      this->sdown = false;
      this->sleft = false;
      this->sright = false;
    }
}

void					Input::serialize(std::ofstream *file)
{
  int					type = T_INPUT;

  file->write(reinterpret_cast<const char *>(&type), sizeof(type));
}
