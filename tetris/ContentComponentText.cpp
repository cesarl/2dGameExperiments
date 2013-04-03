#include				"ContentComponentText.hh"

ContentComponentText::ContentComponentText() :
  AContentComponent(TEXT_TYPE),
  font_(NULL),
  align_(ALLEGRO_ALIGN_LEFT),
  color_(al_map_rgb(0, 0, 0))
{}

ContentComponentText::ContentComponentText(std::string const & fontPath, int size) :
  AContentComponent(TEXT_TYPE),
  font_(NULL),
  align_(ALLEGRO_ALIGN_LEFT),
  color_(al_map_rgb(0, 0, 0))
{
  FontManager				*fontManager;

  fontManager = FontManager::getInstance();
  this->font_ = fontManager->load(fontPath, size);
}

ContentComponentText::ContentComponentText(ALLEGRO_FONT *font) :
  AContentComponent(TEXT_TYPE),
  font_(font),
  align_(ALLEGRO_ALIGN_LEFT),
  color_(al_map_rgb(0, 0, 0))
{
  this->type_ = TEXT_TYPE;
}

ContentComponentText::~ContentComponentText()
{}

void					ContentComponentText::update(Entity *entity, ALLEGRO_EVENT *event)
{
  (void)entity;
  (void)event;
}

void					ContentComponentText::draw(Entity *entity)
{
  if (this->font_)
    al_draw_text(this->font_, this->color_, entity->getX(), entity->getY(), this->align_, this->text_.c_str());
}

void					ContentComponentText::setFont(std::string const & fontPath, int size)
{
  this->font_ = FontManager::getInstance()->load(fontPath, size);
}

void					ContentComponentText::setFont(ALLEGRO_FONT * font)
{
  this->font_ = font;
}

void					ContentComponentText::setAlign(int align)
{
  this->align_ = align;
}

void					ContentComponentText::setColor(ALLEGRO_COLOR color)
{
  this->color_ = color;
}

void					ContentComponentText::operator=(std::string const & str)
{
  this->text_ = str;
}

void					ContentComponentText::operator+=(std::string const & str)
{
  this->text_ += str;
}
