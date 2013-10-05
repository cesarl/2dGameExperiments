#ifndef				__TAG_ID_MANAGER_HPP__
# define		        __TAG_ID_MANAGER_HPP__

#include			<map>
#include			<string>
#include			"Singleton.hpp"

class				TagIdManager : public Singleton<TagIdManager>
{
public:
  unsigned int			getTagId(const std::string &tag)
  {
    std::map<std::string, unsigned int>::iterator it;

    it = list_.find(tag);
    if (it != list_.end())
      return it->second;
    list_.insert(std::pair<std::string, unsigned int>(tag, id_));
    return id_++;
  }
private:
  unsigned int			id_;
  std::map<std::string, unsigned int> list_;
private:
  TagIdManager() :
    id_(0)
  {}
  virtual ~TagIdManager(){}
private:
  friend class Singleton<TagIdManager>;
};

#endif				// __TAG_ID_MANAGER_HPP__
