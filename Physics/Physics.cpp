#include "Physics.hpp"

#include "Resources.hpp"
#include "Entity.hpp"

#include <iostream>
#include <algorithm>
#include <glm/glm.hpp>

Physics::Physics(Resources *resources){
	this->resources = resources;
	xAcceleration = 0;
	frameLag = 0;
	characterXVelocity = 0.0f;
	characterZVelocity = 0.2f;
	characterTilt = 0.0f;
}

void Physics::update(){
	updateCharacter();
}

void Physics::updateCharacter(){
	Entity *character = resources->getCharacterPointer();
	Camera *camera = resources->getCamera();
	Entity *track = resources->getTrackPointer();
	// Update z position
	character->move(glm::vec3(0.0f, 0.0f, 1.0f) * characterZVelocity);
	camera->move(glm::vec3(0.0f, 0.0f, 1.0f) * characterZVelocity);
	track->move(glm::vec3(0.0f, 0.0f, 1.0f) * characterZVelocity);

	int direction = resources->charXAcceleration;
	float thrust = 0.0006;
	float maxXVelocity = 0.014;
	characterXVelocity += direction * thrust;
	if( direction !=0 ){
		frameLag = direction * 10;
	}else if( frameLag > 0 ){
		frameLag--;
		characterXVelocity += thrust;
	}else if( frameLag < 0 ){
		frameLag++;
		characterXVelocity -= thrust;
	}else if( characterXVelocity > 0 ){
		characterXVelocity -= thrust/2;
	}else if( characterXVelocity < 0 ){
		characterXVelocity += thrust/2;
	}
	if( characterXVelocity > maxXVelocity ){
		characterXVelocity = maxXVelocity;
	}
	else if( characterXVelocity < -maxXVelocity ){
		characterXVelocity = -maxXVelocity;
	}
	
	characterXVelocity = std::abs(characterXVelocity) < thrust/2 ? 0 : characterXVelocity;
	character->move(glm::vec3(1.0f, 0.0f, 0.0f) * characterXVelocity);
	resources->charXAcceleration = 0;

	// Update tilt
	characterTilt = - M_PI_4/1.5 * sin(characterXVelocity/maxXVelocity * M_PI_2);
	character->reorient(glm::vec3(0.0f, 0.0f, characterTilt));
}


