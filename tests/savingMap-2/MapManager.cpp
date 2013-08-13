#include			"MapManager.hh"

MapManager::MapManager(int width, int height) :
  cellSize_(40),
  x_(0),
  y_(0),
  width_(width),
  height_(height)
{
  int				ix;

  this->grid_ = new t_tile*[this->height_];
  ix = 0;
  while (ix < width)
    {
      this->grid_[ix] = new t_tile;
	++ix;
    }
}

MapManager::~MapManager()
{}

void				MapManager::move(int x, int y)
{
  this->p_move(x, y);
  if (!this->readExistingWorldChunk())
    this->createNewWorldChunk();
  this->draw();
}

void				MapManager::draw()
{
  int				iy;
  int				ix;

  al_clear_to_color(al_map_rgb(0, 0, 0));
  iy = 0;
  while (iy < this->height_)
    {
      ix = 0;
      while (ix < this->width_)
	{
	  al_draw_filled_rectangle(ix * this->cellSize_,
				   iy * this->cellSize_,
				   ix * this->cellSize_ + this->cellSize_,
				   iy * this->cellSize_ + this->cellSize_,
				   this->grid_[iy][ix].color);
	  ++ix;
	}
      ++iy;
    }

  ix = 0;
  while (ix < 15)
    {
      if (this->entities_[ix].getVisible())
	{
	  this->entities_[ix].draw();
	}
      ++ix;
    }
  al_flip_display();
}

bool				MapManager::readExistingWorldChunk()
{
  ALLEGRO_FILE			*file;

  if (!al_filename_exists(this->filePath_.str().c_str()))
    return false;
  std::cout << "Ca existe !!!" << std::endl;
  file = al_fopen(this->filePath_.str().c_str(), "r");
  for (int iy = 0; iy < this->height_ ; ++iy)
    {
      for (int ix = 0; ix < this->width_ ; ++ix)
	{
	  al_fread(file, &(this->grid_[iy][ix].hexColor), 4);
	  this->p_hexColorToAlColor(&(this->grid_[iy][ix]));
	}
    }


  int				read;
  int				value;
  int				it;

  read = al_fread(file, &(value), 4);
  while (read)
    {
      std::cout << "je lis une entite" << std::endl;
      it = 0;
      while (it < 15 && this->entities_[it].getVisible())
  	++it;
      read = al_fread(file, &value, 4);
      this->entities_[it].setX(value);
      read = al_fread(file, &value, 4);
      this->entities_[it].setY(value);
      read = al_fread(file, &value, 4);
      this->entities_[it].setRadius(value);
      read = al_fread(file, &value, 4);
      this->entities_[it].setHexColor(value);
      entities_[it].setVisible(true);
    }
  al_fclose(file);
  return true;
}

void				MapManager::createNewWorldChunk()
{
  int				color;
  ALLEGRO_FILE			*file;

  std::cout << "le path c'est : " << this->filePath_.str().c_str() << std::endl;
  file = al_fopen(this->filePath_.str().c_str(), "w");
  for (int iy = 0; iy < this->height_ ; ++iy)
    {
      for (int ix = 0; ix < this->width_ ; ++ix)
	{
	  color = rand() % 16777215;
	  this->grid_[iy][ix].hexColor = color;
	  al_fwrite(file, &color, 4);
	  this->p_hexColorToAlColor(&(this->grid_[iy][ix]));
	}
    }
  int				entityNumber = rand() % 10;
  int				i;
  int				it;
  int				value;

  value = 0;
  al_fwrite(file, &value, 4);

  i = 0;
  while (i < entityNumber)
    {
      it = 0;
      while (it < 15 && this->entities_[it].getVisible())
  	{
  	  ++it;
  	}
      this->entities_[it].setVisible(true);
      this->entities_[it].setX(rand() % 400);
      this->entities_[it].setY(rand() % 400);
      this->entities_[it].setRadius(rand() % 60);
      this->entities_[it].setHexColor(rand() % 16777215);
      value = (this->entities_[it].getX());
      al_fwrite(file, &value, 4);
      value = (this->entities_[it].getY());
      al_fwrite(file, &value, 4);
      value = (this->entities_[it].getRadius());
      al_fwrite(file, &value, 4);
      value = (this->entities_[it].getHexColor());
      al_fwrite(file, &value, 4);
      ++i;
    }
  al_fclose(file);
}


void				MapManager::p_hexColorToAlColor(t_tile *tile)
{
  tile->color = al_map_rgb((tile->hexColor >> 16) & 0xFF,
			   (tile->hexColor >> 8) & 0xFF,
			   tile->hexColor & 0xFF);
}

void				MapManager::p_move(int x, int y)
{
  int			it;

  it = 0;
  while (it < 15)
    {
      this->entities_[it].setVisible(false);
      ++it;
    }

  this->filePath_.clear();
  this->filePath_.str("");
  this->x_ += x;
  this->y_ += y;
  this->filePath_ << FILEPREFIX;
  this->filePath_ << this->x_;
  this->filePath_ << "_";
  this->filePath_ << this->y_;
}
