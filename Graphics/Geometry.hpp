#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <glm/glm.hpp>
#include <string>
#include <vector>

// Geometry is an interface for a set of vao, shaders and textures 
class Geometry {
public:

	virtual void render(glm::mat4 projection, glm::mat4 model, glm::mat4 view) = 0;

public:
	std::vector<unsigned int> vaos;
	std::vector<unsigned int> shaders;
	std::vector<unsigned int> textures;
};

#endif // GEOMETRY_H