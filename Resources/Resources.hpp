#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include "Model.hpp"
#include "Entity.hpp"
// #include "Camera.hpp"

#include <string>
// #include <map>

class Resources{
public:
	Resources(int maxEntities, int maxParticleSystems, int maxModels);
	// Logic
	// Get
	Entity *getEntityData();
	// Set

	// Physics
	// Get
	ParticleSystem *getParticleData();
	// Set

	// Graphics
	// Get
	Model *getModelData();
	// Set
	void addModel(Model model, std::string name);
private:
	float dt;
	// Logic
	int nEntities;
	Entity *entities;

	// Physics
	int nParticleSystems;
	ParticleSystem *particleSystems;
	
	// Graphics
	int nModels;
	Model *models;
	std::map<std::string, int> modelNames;
};

#endif