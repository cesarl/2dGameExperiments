#include				"ContentComponentImage.hh"

ContentComponentImage::ContentComponentImage() :
  AContentComponent(),
  bitmap_(NULL)
{
  this->type_ = IMAGE_TYPE;
}

ContentComponentImage::ContentComponentImage(std::string const & imagePath) :
  AContentComponent()
{
  ImageManager				*imageManager;

  imageManager = ImageManager::getInstance();
  this->bitmap_ = imageManager->load(imagePath);
  this->type_ = IMAGE_TYPE;
}

ContentComponentImage::ContentComponentImage(ALLEGRO_BITMAP *image) :
  AContentComponent(),
  bitmap_(image)
{
  this->type_ = IMAGE_TYPE;
}

ContentComponentImage::~ContentComponentImage()
{}

void					ContentComponentImage::setBitmap(std::string const & imagePath)
{
  ImageManager				*imageManager;

  imageManager = ImageManager::getInstance();
  this->bitmap_ = imageManager->load(imagePath);
}

void					ContentComponentImage::setBitmap(ALLEGRO_BITMAP *image)
{
  this->bitmap_ = image;
}

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
