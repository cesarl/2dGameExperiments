#ifndef					__IMAGE_LOADER_HH__
# define				__IMAGE_LOADER_HH__

#include				<allegro5/allegro.h>
#include				"Loader.hpp"
#include				"Image.hpp"

class					ImageLoader : public Loader<Image>
{
public:
  virtual ~ImageLoader()
  {}
  virtual Image				*load(const std::string &file)
  {
    ALLEGRO_BITMAP			*bmp;

    bmp = al_load_bitmap(file.c_str());
    if (!bmp)
      throw LoadingFailed(file, "ImageLoader failed to load image.");
    return new Image(bmp);
  }
  virtual void				save(const Image *, const std::string &name)
  {
    throw LoadingFailed(name, "ImageLoader doesn't support SAVE.");
  }
};

#endif					// __IMAGE_LOADER_HH__
