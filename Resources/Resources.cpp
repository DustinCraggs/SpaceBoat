#include "Resources.hpp"

#include "Model.hpp"
#include "Entity.hpp"

// TODO: Error checking for exceeding bounds of containers

Resources::Resources(int maxEntities, int maxParticleSystems, int maxModels, int maxShaders){
	nEntities = 0;
	nParticleSystems = 0;
	nModels = 0;
	nShaders = 0;
	entities = new Entity[maxEntities];
	particleSystems = new ParticleSystem[maxParticleSystems];
	models = new Model[maxModels];
	shaders = new unsigned int[maxShaders];
}

// Logic
// Get
unsigned int Resources::entitySize(){
	return nEntities;
}

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
unsigned int Resources::particleSystemSize(){
	return nParticleSystems;
}

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
unsigned int Resources::modelSize(){
	return nModels;
}

Model *Resources::getModelData(){
	return models;
}

Model *Resources::getModel(unsigned int i){
	return models + i;
}

Model *Resources::getModel(std::string key){
	return models + modelNames[key];
}

unsigned int Resources::getShader(unsigned int i){
	return shaders[i];
}

unsigned int Resources::getShader(std::string key){
	return shaders[shaderNames[key]];
}

Camera *getCamera(){
	return &camera;
}

GLFWwindow *Resources::getWindow(){

}

// Set

void Resources::setCamera(Camera camera){
	this->camera = camera;
}

unsigned int Resources::addModel(Model model, std::string name){
	models[nModels] = model;
	modelNames[name] = nModels;
	return nModels++;
}

unsigned int Resources::addShader(unsigned int shader, std::string name){
	shaders[i] = shader;
	shaderNames[name] = nShaders;
	return nShaders++;
}










