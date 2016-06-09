
#include <glm/glm.hpp>

class Model{
public:
	Model(std::string path);

	void render(glm::mat4 projection, glm::mat4 model, glm::mat4 view);
private:
	std::vector<unsigned int> vao;
	std::vector<unsigned int> shaders;
	std::vector<unsigned int> textures;

	std::string directory;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	// Generation methods
	unsigned int genVao();
	unsigned int genTexture();
}