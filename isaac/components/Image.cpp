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
				  angle == 0 ? 0 : al_get_bitmap_width(this->bitmap) / 2,
				  angle == 0 ? 0 : al_get_bitmap_height(this->bitmap) / 2,
				  angle == 0 ? position->x : position->x + al_get_bitmap_width(this->bitmap) / 2,
				  angle == 0 ? position->y : position->y + al_get_bitmap_height(this->bitmap) / 2,
				  angle,
				  0);
}

void					Image::setBitmap(std::string const & imagePath)
{
  ImageManager				*imageManager;

  imageManager = ImageManager::getInstance();
  this->bitmap = imageManager->load(imagePath);
  this->path = imagePath;
}

void					Image::serialize(std::ofstream *file)
{
  int					type = T_IMAGE;
  int					s = this->path.size();

  file->write(reinterpret_cast<const char *>(&type), sizeof(type));
  file->write(reinterpret_cast<const char *>(&s), sizeof(int));
  file->write(this->path.c_str(), this->path.size());
}

void					Image::unserialize(std::ifstream *file)
{
  int					s;
  char					p[1024];

  memset(p, 0, 1024);
  file->read(reinterpret_cast<char *>(&s), sizeof(int));
  if (s > 0)
    {
      file->read(p, s);
      this->path = std::string(p);
      std::cout << p << " " << s << std::endl;
      this->bitmap = ImageManager::getInstance()->load(this->path);
    }
}
