#define STBI_IMAGE_IMPLEMENTATION

#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include "Geometry.hpp"
#include "CubeMapTexture.hpp"
#include <glm/glm.hpp>
#include <vector>

class SkyBox : public Geometry {

public:
	SkyBox();

	// Default constructor
	SkyBox(const std::string directory, unsigned int shader);

	// polymorphic render function
	// given a transformation/projection/view, draw the object
	void render(glm::mat4 projection, glm::mat4 model, glm::mat4 view);

	unsigned int activeTexture;

private:
	void genVao();

	// Load a single texture using stbi
	unsigned int loadTexture();

	std::string filenames[6];
};

#endif // SKYBOX_HPP