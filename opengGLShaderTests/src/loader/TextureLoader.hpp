#ifndef					__TEXTURE_LOADER_HH__
# define				__TEXTURE_LOADER_HH__

#include				<iostream>
#include				<fstream>
#include				<string>
#include				<vector>
#include				<allegro5/allegro.h>
#include				<allegro5/allegro_opengl.h>
#include				<glm/glm.hpp>
#include				"Loader.hpp"
#include				"TextureMedia.hpp"

class					TextureLoader : public Loader<TextureMedia>
{
public:
  TextureLoader() : Loader<TextureMedia>()
  {}

  virtual ~TextureLoader()
  {}

  virtual TextureMedia		*load(const File &file, bool force = false)
  {
    std::string				line;
    std::ifstream			myfile(file.getFullName().c_str());
    std::vector<std::string>		list;
    ImageMediaPtr			image;
    GLuint				bufferId;
    std::vector<glm::vec2>		coords;

    if (!myfile.is_open())
      {
	throw LoadingFailed(file.getFullName(), "TextureLoader failed to load texture.");
      }

    while (myfile.good())
      {
	std::getline(myfile, line);
	split(line, list, " ");
	if (list[0] == "IMG" && list.size() == 2)
	  {
	    image = ResourceManager::getInstance().get<ImageMedia>(list[1]);
	  }
	else if (list[0] == "C" && list.size() == 4)
	  {
	    for (unsigned int i = 1; i < 4; ++i)
	      {
		std::vector<std::string>	sub;
		split(list[i], sub, ",");
		if (sub.size() < 2)
		  throw LoadingFailed(file.getFullName(), "TextureLoader error, coords size is not correct.");
		coords.push_back(glm::vec2(std::atof(sub[0].c_str()),
					   std::atof(sub[1].c_str())));
	      }
	  }
      }    

    if (coords.size() == 0 || (coords.size() % 3) != 0)
      {
	throw LoadingFailed(file.getFullName(), "TextureLoader error, coords size is not correct.");
      }

    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, coords.size() * sizeof(glm::vec2), &coords[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return new TextureMedia(bufferId, coords.size(), image, file.getFileName(), force);
  }
  virtual void				save(const TextureMedia *, const std::string &name)
  {
    throw LoadingFailed(name, "TextureLoader doesn't support SAVE.");
  }
};

#endif					// __TEXTURE_LOADER_HH__
