#ifndef					__SAVE_MANAGER_H__
# define				__SAVE_MANAGER_H__

#include				<list>
#include				<string>
#include				<iostream>
#include				<sstream>
#include				<allegro5/allegro.h>

typedef	struct				save_s
{
  char const				*score;
  char const				*user;
}					save_t;

class					SaveManager
{
public:
  ~SaveManager();
  static SaveManager			*getInstance();
  void					load(std::string const & path);
  save_t				*get();
  void					eraseSave(std::string const & userName, int score);
  void					eraseAllSave();
  void					save(std::string const & userName, int score);
private:
  SaveManager();			// private ctor because of singleton pattern
  ALLEGRO_CONFIG			*save_;
  std::string				path_;
  std::list<save_t*>			list_;
  typedef std::list<save_t*>::iterator	iter_t;
private: // member functions
  void					p_saveSaveFile();
  void					p_loadSaveFileInMemory();
};

#endif					// __SAVE_MANAGER_H__
