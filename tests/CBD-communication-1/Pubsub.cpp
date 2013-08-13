#include				"Pubsub.hh"

Pubsub::Pubsub()
{}

Pubsub::~Pubsub(){};

Pubsub					*Pubsub::getInstance()
{
  static Pubsub				that;
  return &that;
}

void					Pubsub::subscribe(AComponent *component, std::string const & message)
{
  std::list<AComponent*>		list;
  t_iter_map				it_map;

  it_map = this->map_.find(message);
  if (it_map == this->map_.end())
    {
      list.push_back(component);
      this->map_.insert(t_pair_map(message, list));
    }
  else
    {
      it_map->second.push_back(component);
    }
}

void				Pubsub::publish(std::string const &message)
{
  t_iter_map				it_map;
  t_iter_list				it_list;


  it_map = this->map_.find(message);
  if (it_map == this->map_.end())
    {
      return;
    }
  it_list = it_map->second.begin();
  while (it_list != it_map->second.end())
    {
      (*it_list)->receiveSubscription(message);
      ++it_list;
    }
}
