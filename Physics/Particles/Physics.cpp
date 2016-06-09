#include "Physics.hpp"

#include <iostream>
#include <chrono>
#include <random>
#include <glm/glm.hpp>

#define MAX_PARTICLES 10000

// Aspect is x/y
Physics::Physics(float aspect, float initialIntensity) : 
	x_distribution(-aspect, aspect), y_distribution(-1.0f, 1.0f),
	gen_distribution(initialIntensity, initialIntensity/10),
	particles(10000) {
	unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
	// generator(seed);
	generateInitialState(aspect);
}

void Physics::generateInitialState(float intensity){
	for( int i=0; i<1500; i++ ){
		particles.add(glm::vec3(nextXCoord(), nextYCoord(), 0.0f), glm::vec3(0.1f, 0.0f, 0.0f), glm::vec3(0.0f, 0.4f, 1.0f));
	}
}

void Physics::nextFrame(float time, float intensity){
	// Update phase
	update(time);

	// Collision phase
	collide();
 
	// Generation phase
	generate(time, intensity);
}

void Physics::update(float time_delta){
	for( int i=0; i<particles.nParticles(); i++ ){
		particles.positionAt(i) = particles.positionAt(i) + particles.velocityAt(i) * time_delta;
	}
}

void Physics::collide(){

}

void Physics::generate(float time_delta, float intensity){

}

float Physics::nextXCoord(){
	return x_distribution(generator);
}

float Physics::nextYCoord(){
	return y_distribution(generator);
}

float Physics::nextParticleNumber(){
	return gen_distribution(generator);
}

// Testing

unsigned int Physics::nParticles(){
	return particles.nParticles();
}

float *Physics::particleData(){
	return particles.getPosPointer();
}

float *Physics::colourData(){
	return particles.getColPointer();
}