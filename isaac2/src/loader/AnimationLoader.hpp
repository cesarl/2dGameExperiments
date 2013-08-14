#ifndef					__ANIMATION_LOADER_HPP__
# define				__ANIMATION_LOADER_HPP__

#include				<iostream>
#include				<fstream>
#include				<string>
#include				"Animation.hpp"
#include				"strUtil.hpp"
#include				"ResourceManager.hpp"

class					AnimationLoader : public Loader<Animation>
{
public:
  AnimationLoader() : Loader<Animation>()
  {}

  virtual ~AnimationLoader()
  {}

  virtual Animation			*load(const File &file, bool force = false)
  {
    std::string				line;
    std::ifstream			myfile(file.getFullName().c_str());

    if (!myfile.is_open())
      {
	throw LoadingFailed(file.getFullName(), "AnimationLoader failed to load animation.");
      }

    std::string				name;
    std::string				imgFile;
    int					stepNumber = 0;
    double				*timeSteps = NULL;
    bool				reverse = false;
    int					cycleNumber = 0;
    Animation::Coords			*coords = NULL;
    ImagePtr				image;

    while (myfile.good())
      {
	std::vector<std::string> list;
	std::getline(myfile, line);
	split(line, list, " ");
	if (list.size() < 2)
	  continue;
	if (list[0] == "NAME")
	  {
	    name = list[1];
	  }
	else if (list[0] == "IMG")
	  {
	    imgFile = list[1];
	    image = ResourceManager::getInstance().get<Image>(imgFile);
	  }
	else if (list[0] == "STEPNB")
	  {
	    stepNumber = std::atoi(list[1].c_str());
	  }
	else if (list[0] == "REVERSE")
	  {
	    reverse = list[1] == "true" ? true : false;
	  }
	else if (list[0] == "CYCLENB")
	  {
	    cycleNumber = std::atoi(list[1].c_str());
	  }
	(void)coords;
	(void)timeSteps;
	(void)force;
      }
    std::cout << name << " " << imgFile << " " << stepNumber << " " << reverse << " " << cycleNumber << std::endl;	myfile.close();
    return new Animation(image, timeSteps, stepNumber, reverse, cycleNumber, coords, name, force);
  }

  virtual void				save(const Animation *, const std::string &name)
  {
    throw LoadingFailed(name, "AnimationLoader doesn't support SAVE.");
  }

};

#endif					// __ANIMATION_LOADER_HPP__
