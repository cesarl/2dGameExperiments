#include				<iostream> // for debug
#include				"Image.hh"
#include				"ComponentTypes.hh"

Image::Image(Entity *entity) : AComponent(entity, T_IMAGE, 0, 1)
{
  POSITION(entity);
  VISIBILITY(entity);
  ROTATION(entity);
  this->bitmap = NULL;
}

Image::~Image()
{}

void					Image::update(double time)
{
  (void)time;
}

void					Image::draw()
{
  Position				*position = POSITION(this->entity);
  unsigned char				opacity = VISIBILITY(this->entity)->opacity;
  float					angle = ROTATION(this->entity)->angle;

  if (this->bitmap)
    al_draw_tinted_rotated_bitmap(this->bitmap,
				  al_map_rgba(opacity, opacity, opacity, opacity),
				  al_get_bitmap_width(this->bitmap) / 2,
				  al_get_bitmap_height(this->bitmap) / 2,
				  position->x,
				  position->y,
				  angle,
				  0);
}

void					Image::setBitmap(std::string const & imagePath)
{
  ImageManager				*imageManager;

  imageManager = ImageManager::getInstance();
  this->bitmap = imageManager->load(imagePath);
}

void					Image::setBitmap(ALLEGRO_BITMAP *image)
{
  this->bitmap = image;
}
