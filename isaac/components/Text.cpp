#include				<iostream> // for debug
#include				"Text.hh"
#include				"ComponentTypes.hh"

Text::Text(Entity *entity) : AComponent(entity, T_TEXT, 0, 1)
{
  POSITION(entity);
  VISIBILITY(entity);
  this->font = NULL;
  this->color = al_map_rgb(0, 0, 0);
  this->align = ALLEGRO_ALIGN_LEFT;
}

Text::~Text()
{}

void					Text::update(double time)
{
  (void)time;
}

void					Text::draw()
{
  Position				*position = POSITION(this->entity);
  unsigned char				opacity = VISIBILITY(this->entity)->opacity;
  unsigned char				r,g,b;

  al_unmap_rgb(this->color, &r, &g, &b);
  if (this->font)
    al_draw_text(this->font, al_map_rgba(r, g, b, opacity), position->x, position->y, this->align, this->text.c_str());
}

void					Text::setFont(std::string const & fontPath, int size)
{
  FontManager				*fontManager;

  fontManager = FontManager::getInstance();
  this->font = fontManager->load(fontPath, size);
  if (this->font)
    this->fontPath = fontPath;
}

void					Text::operator=(std::string const & str)
{
  this->text = str;
}

void					Text::operator+=(std::string const & str)
{
  this->text += str;
}

void					Text::serialize(std::ofstream &file)
{
  int					type = T_TEXT;

  Archive::serialize(file, type);
  Archive::serialize(file, this->fontPath);
  Archive::serialize(file, this->text);
}

void					Text::unserialize(std::ifstream &file)
{
  Archive::unserialize(file, this->fontPath);
  Archive::unserialize(file, this->text);
}
