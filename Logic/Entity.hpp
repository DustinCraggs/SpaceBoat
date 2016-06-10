#ifndef ENTITY_H
#define ENTITY_H

#include "Geometry.hpp"

class Entity{
public:
	Geometry *geometry;

	glm::vec3 position;
	glm::vec orientation;
	glm::vec3 scale;

	glm::mat4 transformation;
private:
	Entity(Model *model);
	void render(glm::mat4 projection, glm::mat4 view);

	// Getting tranformation properties
	glm::mat4 getTransform();
	glm::vec3 getPosition();
	glm::vec3 getOrientation();
	glm::vec3 getScale();

	// Setting tranformation properties
	void reposition(glm::vec3 pos);
	void reposition(float xpos, float ypos, float zpos);

	void reorient(float radians, glm::vec3 axis);
	void reorient(glm::vec3 orientation);
	void reorient(float xrad, float yrad, float zrad);

	void rescale(glm::vec3 scale);
	void rescale(float xscale, float yscale, float zscale);
	void resize(float scaleFactor);

	// Altering transformation properties
	void move(float distance, glm::vec3 direction);
	void move(glm::vec3 movement);
	void move(float xdist, float ydist, float zdist);

	void rotate(float radians, glm::vec3 axis);
	void rotate(glm::vec3 rotation);
	void rotate(float xrad, float yrad, float zrad);

	void stretch(glm::vec3 stretchFactors);
	void stretch(float xstretch, float ystretch, float zstretch);
	void expand(float scaleFactor);
}

#endif