#ifndef MODEL_H
#define MODEL_H

#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "../Libs/tiny_obj_loader.h"

class Model{
public:
	Model(std::string path);

	void render(glm::mat4 projection, glm::mat4 model, glm::mat4 view);
private:
	std::vector<unsigned int> vaos;
	std::vector<unsigned int> shaders;
	std::vector<unsigned int> textures;

	std::string objDir;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	void renderShape(unsigned int i, glm::mat4 projection, glm::mat4 model, glm::mat4 view);
	// Generation methods
	void genVaos();
	void loadVao(unsigned int i);
	void genTextures();
	void loadTexture(std::string path);
	void loadDefaultTexture();
};

#endif