#include				"TextInput.hh"
#include				"ComponentTypes.hh"

#include				<iostream> //pour le debug - a virer

TextInput::TextInput(Entity *entity) : AComponent(entity, T_TEXT_INPUT)
{
  TEXT(entity);
}

TextInput::~TextInput()
{}

void					TextInput::update(double time)
{
  (void)(time);
}

void					TextInput::draw()
{}

void					TextInput::input(ALLEGRO_EVENT *event)
{
  std::ostringstream                    o;
  Text					*text;

  text = TEXT(this->entity);
  if (event->type != ALLEGRO_EVENT_KEY_CHAR)
    return;
  if (event->keyboard.keycode == ALLEGRO_KEY_BACKSPACE && text->text.length())
    {
      text->text.erase(text->text.length() - 1, 1);
    }
  else if (event->keyboard.keycode >= ALLEGRO_KEY_A && event->keyboard.keycode <= ALLEGRO_KEY_Z)
    {
      o << (char)event->keyboard.unichar;
      text->text += (o.str());
    }
}
