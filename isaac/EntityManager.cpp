#include			<iostream> // for debug /!\ //
#include			"EntityManager.hh"

EntityManager::EntityManager()
{}

EntityManager::~EntityManager()
{}

EntityManager			*EntityManager::getInstance()
{
  static EntityManager			that;

  return &that;
}

bool				EntityManager::generate(int seed)
{
  generationRule		r;

  while(!this->generationRules_.empty())
    {
      r = this->generationRules_.front();
      if (!r(this, seed))
	return false;
    this->generationRules_.pop();
  }
 return true;
}

void				EntityManager::clear()
{
  std::list<Entity*>::iterator	it;

  it = this->list_.begin();
  while (it != this->list_.end())
    {
      delete (*it);
      ++it;
    }
  this->list_.clear();
}

void				EntityManager::pushGenerationRule(generationRule fn)
{
  this->generationRules_.push(fn);
}

bool				EntityManager::unserialize()
{
  return true;
}

void				EntityManager::update()
{
  std::list<Entity*>::iterator	it;

  it = this->list_.begin();
  while (it != this->list_.end())
    {
      (*it)->update();
      CollisionManager::getInstance()->add(*it);
      ++it;
    }
  CollisionManager::getInstance()->update();
}

void				EntityManager::draw()
{
  std::list<Entity*>::iterator	it;

  it = this->list_.begin();
  while (it != this->list_.end())
    {
      DrawManager::getInstance()->add(*it);
      ++it;
    }
}

Entity				*EntityManager::create()
{
  Entity			*tmp;

  tmp = new Entity;
  if (!tmp)
    return NULL;
  this->list_.push_back(tmp);
  return tmp;
}

bool				EntityManager::serialize(std::string const & path, std::string const & name)
{
  std::ostringstream		fileName;
  std::ofstream			myFile;
  std::list<Entity*>::iterator	it;

  fileName << path << name << ".bin";
  myFile.open(fileName.str().c_str(), std::ios::out | std::ios::binary);
  it = this->list_.begin();
  while (it != this->list_.end())
    {
      (*it)->serialize(&myFile);
      ++it;
    }
  myFile.close();
  return true;
}
