#include				"ContentComponentImage.hh"

ContentComponentImage::ContentComponentImage() :
  bitmap_(NULL)
{}

ContentComponentImage::ContentComponentImage(std::string const & imagePath)
{
  ImageManager				*imageManager;

  imageManager = ImageManager::getInstance();
  this->bitmap_ = imageManager->load(imagePath);
}

ContentComponentImage::ContentComponentImage(ALLEGRO_BITMAP *image) :
  bitmap_(image)
{}

ContentComponentImage::~ContentComponentImage()
{}

void					ContentComponentImage::update(Entity *entity, ALLEGRO_EVENT *event)
{
  return;
  (void)(entity);
  (void)(event);
}

void					ContentComponentImage::draw(Entity *entity)
{
  if (this->bitmap_)
    al_draw_bitmap(this->bitmap_, entity->getX(), entity->getY(), 0);
  else
    std::cerr << "Error : ContentComponentImage - Draw() - Bitmap isn't set" << std::endl;
}
