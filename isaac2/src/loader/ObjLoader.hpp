#ifndef					__OBJ_LOADER_HH__
# define				__OBJ_LOADER_HH__

#include				<iostream>
#include				<fstream>
#include				<string>
#include				<vector>
#include				<allegro5/allegro.h>
#include				<allegro5/allegro_opengl.h>
#include				<glm/glm.hpp>
#include				"Loader.hpp"
#include				"ObjModel.hpp"

class					ObjLoader : public Loader<ObjModel>
{
public:
  ObjLoader() : Loader<ObjModel>()
  {}

  virtual ~ObjLoader()
  {}

  virtual ObjModel			*load(const File &file, bool force = false)
  {
    std::vector<unsigned int>		vertexI;
    std::vector<unsigned int>		uvI;
    std::vector<unsigned int>		normalI;
    std::vector<glm::vec3>		vertices;
    std::vector<glm::vec2>		uvs;
    std::vector<glm::vec3>		normals;
    std::string				line;
    std::ifstream			myfile(file.getFullName().c_str());
    std::vector<std::string>		list;

    if (!myfile.is_open())
      {
	throw LoadingFailed(file.getFullName(), "ObjLoader failed to load .obj file.");
      }

    while (myfile.good())
      {
	std::getline(myfile, line);
	split(line, list, " ");
	if (list[0] == "v")
	  {
	    glm::vec3			vertex;

	    vertex = glm::vec3(std::atof(list[1].c_str()),
			       std::atof(list[2].c_str()),
			       std::atof(list[3].c_str()));

	    vertices.push_back(vertex);
	  }
	else if (list[0] == "vt")
	  {
	    glm::vec2			uv;

	    uv = glm::vec2(std::atof(list[1].c_str()),
			   std::atof(list[2].c_str()));

	    uvs.push_back(uv);
	  }
	else if (list[0] == "vn")
	  {
	    glm::vec3			n;

	    n = glm::vec3(std::atof(list[1].c_str()),
			  std::atof(list[2].c_str()),
			  std::atof(list[3].c_str()));

	    normals.push_back(n);
	  }
	else if (list[0] == "f")
	  {
	    for (unsigned int i = 1; i < 4; ++i)
	      {
		std::vector<std::string> l;

		split(list[i], l, "/");
		vertexI.push_back(std::atof(l[0].c_str()));
		uvI.push_back(std::atof(l[1].c_str()));
		normalI.push_back(std::atof(l[2].c_str()));
	      }
	  }
      }

    std::vector<glm::vec3>		resVertices;
    std::vector<glm::vec2>		resUvs;
    std::vector<glm::vec3>		resNormals;

    for (unsigned int i = 0; i < vertexI.size(); ++i)
      {
	glm::vec3			vertex;

	vertex = vertices[vertexI[i] - 1];
	resVertices.push_back(vertex);

	glm::vec2			uv;

	uv = uvs[uvI[i] - 1];
	resUvs.push_back(uv);	

	glm::vec3			n;

	n = normals[normalI[i] - 1];
	resNormals.push_back(vertex);
      }

    GLuint				vertexBuffer;

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, resVertices.size() * sizeof(glm::vec3), &resVertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint				uvBuffer;

    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, resUvs.size() * sizeof(glm::vec2), &resUvs[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return new ObjModel(vertexBuffer, uvBuffer, resVertices.size(), file.getFileName(), force);
  }
  virtual void				save(const ObjModel *, const std::string &name)
  {
    throw LoadingFailed(name, "ObjLoader doesn't support SAVE.");
  }
};

#endif					// __OBJ_LOADER_HH__
