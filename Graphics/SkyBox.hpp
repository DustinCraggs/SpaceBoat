#define STBI_IMAGE_IMPLEMENTATION

#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include "Geometry.hpp"
#include "CubeMapTexture.hpp"
#include <glm/glm.hpp>
#include <vector>

class SkyBox : public Geometry {

public:

	// Default constructor
	SkyBox();

	// polymorphic render function
	// given a transformation/projection, draw the object
	void render();
	void render(glm::mat4 projection, glm::mat4 model, glm::mat4 view);

	// Given a directory and a vector of filepaths, load a new texture
	void loadNewTexture(const std::string& director, 
		const std::vector<std::string>& filepaths);

	unsigned int activeTextureID;

	void setActiveTextureID(unsigned int);

private:
	void genVao();

	// Load a single texture using stbi
	unsigned int loadTexture();

	std::string filenames[6];
};

#endif // SKYBOX_HPP