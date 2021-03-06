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
  this->emptyTrash();
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

void				EntityManager::erase(Entity *entity)
{
   this->trash_.push(entity);
}

bool				EntityManager::serialize(std::string const & path, std::string const & name)
{
  std::ostringstream		fileName;
  std::ofstream			myFile;
  std::list<Entity*>::iterator	it;

  fileName << path << name << ".bin";

  if (!Archive::open(myFile, fileName.str()))
    return false;

  it = this->list_.begin();
  while (it != this->list_.end())
    {
      (*it)->serialize(myFile);
      ++it;
    }
  myFile.close();
  return true;
}

bool				EntityManager::unserialize(std::string const & path, std::string const & name)
{
  std::ostringstream		fileName;
  std::ifstream			myFile;
  typename std::list<Entity*>::iterator it;
  Entity			*tmp;

  fileName << path << name << ".bin";
  if (!al_filename_exists(fileName.str().c_str()))
    return false;

  if (!Archive::open(myFile, fileName.str()))
    return false;

  while (!myFile.eof())
    {
      tmp = this->create();
      if (!tmp)
	return false;
      tmp->unserialize(myFile);
    }

  myFile.close();
  return true;
}

void				EntityManager::emptyTrash()
{
  Entity			*r;

  while(!this->trash_.empty())
    {
      r = this->trash_.front();
      this->list_.remove(r);
      delete r;
    this->trash_.pop();
  }
}
