#ifndef TRACK_HPP
#define TRACK_HPP

#include <glm/glm.hpp>

#include "Geometry.hpp"

class Plane : public Geometry {

public:
	// Default constructor
	Plane();
	Plane(unsigned int shader);

	void render(glm::mat4 projection, glm::mat4 model, glm::mat4 view);

private:
	void genVao();
};

#endif // TRACK_HPP