#include				"SaveManager.hh"

SaveManager::SaveManager()
{}

SaveManager::~SaveManager()
{
  p_saveSaveFile();
}

SaveManager				*SaveManager::getInstance()
{
  static SaveManager			that;
  return &that;
}

void					SaveManager::load(std::string const & path)
{
  if (this->save_)
    this->p_saveSaveFile();
  this->save_ = al_load_config_file(path.c_str());
  if (!this->save_)
    {
      this->save_ = al_create_config();
    }
  if (!this->save_)
    {
      std::cerr << "Error : SaveManager - Unable to load / create save file" << std::endl;
      return;
    }
  this->path_ = path.c_str();
  p_loadSaveFileInMemory();
}

void					SaveManager::save(std::string const & userName, int score)
{
  std::ostringstream			tmp;

  tmp << score;
  if (!this->save_)
    return;
  al_add_config_section(this->save_, userName.c_str());
  al_set_config_value(this->save_, userName.c_str(), "score", tmp.str().c_str());
  p_loadSaveFileInMemory();
}

void					SaveManager::p_saveSaveFile()
{
  if (!this->path_.empty())
    {
      if (!al_save_config_file(this->path_.c_str(), this->save_))
	std::cerr << "Error : SaveManager - Unable to save saveFile to disk" << std::endl;
    }
}

void					SaveManager::p_loadSaveFileInMemory()
{
  ALLEGRO_CONFIG_SECTION		*section;
  const char				*name;
  save_t				*save;

  name = al_get_first_config_section(this->save_, &section);
  while (name)
    {
      save = new save_t;
      save->user = name;
      save->score = al_get_config_value(this->save_, name, "score");
      name = al_get_next_config_section(&section);
    }
}

