#include <glm/glm.hpp>
#include "BackSwapArray.hpp"

class Particles{
public:
	Particles(unsigned int max_size);
	void add(glm::vec3 position, glm::vec3 colour);
private:	
	BackSwapArray<float> positions;
	BackSwapArray<float> colours;
};