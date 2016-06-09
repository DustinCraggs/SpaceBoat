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

// Set
unsigned int Resources::addEntity(Entity entity){
	entities[nEntities] = entity;
	return nEntities++;
}

// Physics
// Get
ParticleSystem *Resources::getParticleData(){
	return particleSystems;
}

// Set
unsigned int Resources::addParticleSystem(ParticleSystem particleSystem){
	particleSystems[nParticleSystems] = particleSystem;
	return nParticleSystems++;
}

// Graphics
// Get
Model *Resources::getModelData(){
	return models;
}

// Set
unsigned int Resources::addModel(Model model, std::string name){
	models[nModels] = model;
	modelNames[name] = nModels;
	return nModels++;
}


