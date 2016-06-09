#include "Resources.hpp"

#include "Model.hpp"
#include "Entity.hpp"

Resources::Resources(int maxEntities, int maxParticleSystems, int maxModels){
	nEntities = 0;
	nParticleSystems = 0;
	nModels = 0;
	entities = new Entity[maxEntities];
	particleSystems = new ParticleSystem[maxParticleSystems];
	models = new Model[maxModels];
}

// Logic
// Get
Entity *Resources::getEntityData(){
	return entities;
}

// Physics
// Get
ParticleSystem *Resources::getParticleData(){
	return particleSystems;
}

// Graphics
// Get
Model *Resources::getModelData(){
	return models;
}

// Set
void Resources::addModel(Model model, std::string name){
	models[nModels] = model;
}


