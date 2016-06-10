#include "ParticleSystem.hpp"

#include <iostream>
#include <glm/glm.hpp>
#include "BackSwapArray.hpp"


ParticleSystem::ParticleSystem(unsigned int max_size) : positions(max_size), velocities(max_size), colours(max_size){
	m_nParticles = 0;
	m_capacity = max_size;
}

void ParticleSystem::add(glm::vec3 position, glm::vec3 velocity, glm::vec3 colour){
	positions.add(position);
	velocities.add(velocity);
	colours.add(colour);
	m_nParticles++;
}

void ParticleSystem::remove(unsigned int i){
	positions.remove(i);
	velocities.remove(i);
	colours.remove(i);
	m_nParticles--;
}

glm::vec3 &ParticleSystem::positionAt(unsigned int i){
	return positions[i];
}

glm::vec3 &ParticleSystem::velocityAt(unsigned int i){
	return velocities[i];
}

glm::vec3 &ParticleSystem::colourAt(unsigned int i){
	return colours[i];
}

float *ParticleSystem::getPosPointer(){
	return (float*)positions.data();
}

float *ParticleSystem::getColPointer(){
	return (float*)colours.data();
}

unsigned int ParticleSystem::nParticles(){
	return m_nParticles;
}

unsigned int ParticleSystem::capacity(){
	return m_capacity;
}


// TESTING
// int main(){
// 	ParticleSystem ps(100);
// 	ps.add(glm::vec3(0.8f, 0.7f, 0.3f), glm::vec3(0.3f, 0.5f, 0.8f));
// 	ps.add(glm::vec3(0.7f, 0.7f, 0.3f), glm::vec3(0.3f, 0.5f, 0.8f));
// 	ps.add(glm::vec3(0.6f, 0.7f, 0.3f), glm::vec3(0.3f, 0.5f, 0.8f));
// 	float *data = ps.getPosPointer();
// 	for( int i=0; i<3*3; i++ ){
// 		std::cout << *(data + i) << std::endl;
// 	}
// }