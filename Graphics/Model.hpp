#ifndef MODEL_H
#define MODEL_H

#include "Geometry.hpp"

#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "tiny_obj_loader.h"

class Model : public Geometry {
public:
	Model(std::string path);
	Model(std::string path, unsigned int);

	void render(glm::mat4 projection, glm::mat4 model, glm::mat4 view);
private:
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