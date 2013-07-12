#ifndef				__MAP_GENERATOR_HPP__
# define			__MAP_GENERATOR_HPP__

#include			<vector>
#include			"EntityManager.hpp"
#include			"EntityManager.hpp"

class				MapGenerator
{
public:
  MapGenerator() :
    list_(NULL),
    open_(NULL),
    wg_(NULL)
  {}
  ~MapGenerator()
  {
    clear();
  }

  void				clear()
  {
    t_iter			it;

    it = entities_.begin();
    while (it != entities_.end())
      {
	EntityManager::getInstance().eraseEntity(*it);
	++it;
      }
    entities_.clear();
    if (list_)
      delete list_;
    if (wg_)
      delete wg_;
    if (open_)
      delete open_;
  }

  void				setUnion(int p, int q)
  {
    int				i = findRoot(p);
    int				j = findRoot(q);

    if (wg_[i] < wg_[j])
      {
	list_[i] = j;
	wg_[j] += wg_[i];
      }
    else
      {
	list_[j] = i;
	wg_[i] += wg_[j];
      }
  }

  bool				isConnected(int p, int q)
  {
    return (findRoot(p) == findRoot(q));
  }


  int				findRoot(int i)
  {
    while (i != list_[i])
      {
	i = list_[i];
      }
    return i;
  }

  bool				open(unsigned int p)
  {
    if (open_[p])
      return false;

    unsigned int		x = p % width_;
    unsigned int		y = p / width_;

    if (x == 0 || x >= width_ - 1 || y == 0 || y >= height_ - 1)
      return false;
    open_[p] = 1;

    setUnionAfterOpen(p, x, y);

    return true;
  }

  void				setUnionAfterOpen(unsigned int p, unsigned int x, unsigned int y)
  {
    // union left
    if (x > 0 && open_[p - 1])
      setUnion(p, p - 1);

    // union right
    if (x < width_ - 1 && open_[p + 1])
      setUnion(p, p + 1);

    // union up
    if (y > 0 && open_[p - width_])
      setUnion(p, p - width_);

    // union down
    if (y < height_ - 1 && open_[p + width_])
      setUnion(p, p + width_);
  }

  void				generate(unsigned int width, unsigned int height)
  {
    clear();
    start_ = width / 2;
    end_ = (height - 1) * width + width / 2;
    width_ = width;
    height_ = height;

    if (!(list_ = new int[width * height]) 
	|| !(wg_ = new unsigned int[width * height])
	|| !(open_ = new unsigned int[width * height]))
      {
	std::cout << "Out of memory" << std::endl;
      }
    for (unsigned int i = 0; i < width * height; ++i)
      {
    	list_[i] = i;
    	open_[i] = 0;
    	wg_[i] = 1;
      }
    open_[start_] = 1;
    open_[end_] = 1;

    while (!isConnected(start_, end_))
      {
    	while (!open(rand() % (width * height)))
    	  ;
      }

    start_ = (height / 2) * width;
    end_ =  (height / 2 + 1) * width - 1;

    for (unsigned int i = 0; i < width * height; ++i)
      {
	list_[i] = i;
	// open_[i] = 0;
	wg_[i] = 1;
      }

    open_[start_] = 1;
    open_[end_] = 1;

    for (unsigned int i = 0; i < width * height; ++i)
      {
	if (open_[i])
	  {
	    setUnionAfterOpen(i, i % width, i / width);
	  }
      }

    std::cout << start_ << std::endl;
    std::cout << end_ << std::endl;
    while (!isConnected(start_, end_))
      {
    	while (!open(rand() % (width * height)))
    	  ;
      }

    for (unsigned int i = 0; i < width * height; ++i)
      {
	unsigned int				e;

	e = EntityManager::getInstance().newEntity();
	Position &posComponent = ComponentManager::getInstance().addComponent<Position>(e);
	Img &imgComponent = ComponentManager::getInstance().addComponent<Img>(e);
	Scale &scaleComponent = ComponentManager::getInstance().addComponent<Scale>(e);
	Color &colorComponent = ComponentManager::getInstance().addComponent<Color>(e);
	ComponentManager::getInstance().addComponent<Rotation>(e);

	if (open_[i])
	  colorComponent.set(1.0f, 0.0f, 1.0f, 1.0f);
	posComponent.position = Vector3d(i % width_ * (900 / width_), i / width_ * (700 / height_), 0);
	imgComponent.img = ResourceManager::getInstance().get<Image>("stars.png");
	scaleComponent.scale = Vector3d(900 / width_, 700 / height, 0);
	this->entities_.push_back(e);
      }
  }
private:
  typedef std::vector<unsigned int>::iterator t_iter;
  typedef std::vector<unsigned int>::const_iterator t_const_iter;

  int				*list_;
  unsigned int			*open_;
  unsigned int			*wg_;
  std::vector<unsigned int>	entities_;
  unsigned int			width_;
  unsigned int			height_;
  unsigned int			start_;
  unsigned int			end_;
};






#endif				// __MAP_GENERATOR_HPP__
