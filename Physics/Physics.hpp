#ifndef PHYSICS_H
#define PHYSICS_H

#include "Resources.hpp"
#include "Entity.hpp"

#include <glm/glm.hpp>

class Physics{
public:
	Physics(Resources *resources);
	void update();
private:
	Resources *resources;

	// Character
	int xAcceleration;
	int frameLag;
	float characterXVelocity;
	float characterZVelocity;
	float characterTilt;
	void updateCharacter();
};

#endif