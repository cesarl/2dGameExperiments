#include			"Collection.hh"

template <typename T>
Collection<T>::Collection() :
  grid_(NULL)
{
}

template <typename T>
Collection<T>::~Collection()
{
  this->clear();
}

template <typename T>
bool				Collection<T>::save(std::string const & path, std::string const & name, int x, int y)
{
  std::ostringstream		fileName;
  std::ofstream			myFile;
  typename std::vector<T*>::iterator it;

  fileName << path << name << x << "-" << y  << ".bin";
  myFile.open(fileName.str().c_str(), std::ios::out | std::ios::binary);
  it = this->go_.begin();
  while (it != this->go_.end())
    {
      (*it)->serialize(&myFile);
      ++it;
    }
  myFile.close();
  return true;
}

template <typename T>
bool				Collection<T>::load(std::string const & path, std::string const & name, int x, int y)
{
  std::ostringstream		fileName;
  std::ifstream			myFile;
  typename std::vector<T*>::iterator it;
  T				*tmp;

  fileName << path << name << x << "-" << y  << ".bin";
  if (!al_filename_exists(fileName.str().c_str()))
    return false;

  myFile.open(fileName.str().c_str(), std::ios::out | std::ios::binary);

  while (!myFile.eof())
    {
      tmp = new T;
      tmp->unserialize(&myFile);
      this->go_.push_back(tmp);
    }

  myFile.close();
  return true;
}

template <typename T>
void				Collection<T>::clear()
{
  typename std::vector<T*>::iterator it;

  it = this->go_.begin();
  while (it != this->go_.end())
    {
      delete *it;
      ++it;
    }
  this->go_.clear();
}

template <typename T>
void				Collection<T>::update(ALLEGRO_EVENT *event)
{
  typename std::vector<T*>::iterator it;

  it = this->go_.begin();
  while (it != this->go_.end())
    {
      (*it)->update();
      ++it;
    }
  (void)event;
}

template <typename T>
void				Collection<T>::draw(ALLEGRO_EVENT *event)
{
  typename std::vector<T*>::iterator it;

  it = this->go_.begin();
  while (it != this->go_.end())
    {
      (*it)->draw();
      ++it;
    }
  (void)event;
}

template <typename T>
std::vector<Entity*>		*Collection<T>::getSelection(int x, int y, int w, int h)
{
  typename std::vector<T*>::iterator it;

  it = this->go_.begin();
  while (it != this->go_.end())
    {
      //(*it)->draw();
      ++it;
    }
  (void)(x);(void)(y);(void)(w);(void)(h);
  return &(this->selection_);
}

template <typename T>
std::vector<Entity*>		*Collection<T>::getSelection(Entity *entity)
{
  typename std::vector<T*>::iterator it;

  it = this->go_.begin();
  this->selection_.clear();
  while (it != this->go_.end())
    {
      if (BOUNDING_BOX(entity)->collide(*it))
	this->selection_.push_back(*it);
      ++it;
    }
  return &(this->selection_);
}

template <typename T>
void			Collection<T>::attachGrid(Grid *grid)
{
  this->grid_ = grid;
}

template <typename T>
void			Collection<T>::fillGrid()
{
  typename std::vector<T*>::iterator it;

  if (!this->grid_)
    return;
  it = this->go_.begin();
  while (it != this->go_.end())
    {
      this->grid_->add(*it);
      ++it;
    }
}
