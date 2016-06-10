#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <glm/glm.hpp>
#include "BackSwapArray.hpp"

class ParticleSystem{
public:
	ParticleSystem(unsigned int max_size = 10000);
	void add(glm::vec3 position, glm::vec3 velocities, glm::vec3 colour);
	void remove(unsigned int i);

	// Get elements
	glm::vec3 &positionAt(unsigned int i);
	glm::vec3 &velocityAt(unsigned int i);
	glm::vec3 &colourAt(unsigned int i);

	// Get data pointers
	float *getPosPointer();
	float *getColPointer();

	// Get size/capacity
	unsigned int nParticles();
	unsigned int capacity();
private:
	unsigned int m_nParticles;
	unsigned int m_capacity;
	BackSwapArray<glm::vec3> positions;
	BackSwapArray<glm::vec3> velocities;
	BackSwapArray<glm::vec3> colours;
};

#endif