#include "Resources.hpp"

#include "Model.hpp"
#include "Entity.hpp"
#include "Camera.hpp"
#include "ParticleSystem.hpp"
#include "SkyBox.hpp"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// TODO: Error checking for exceeding bounds of containers

Resources::Resources(unsigned int maxEntities, unsigned int maxParticleSystems, unsigned int maxModels, unsigned int maxShaders){
	nEntities = 0;
	nParticleSystems = 0;
	nModels = 0;
	nShaders = 0;
	entities = new Entity[maxEntities];
	particleSystems = new ParticleSystem[maxParticleSystems];
	models = new Model[maxModels];
	shaders = new unsigned int[maxShaders];
	std::cout << "Resources instantiated" << std::endl;
}

// Logic
// Get
unsigned int Resources::entitySize(){
	return nEntities;
}

Entity *Resources::getEntityData(){
	return entities;
}

Entity *Resources::getEntity(unsigned int i){
	return entities+i;
}

// Set
unsigned int Resources::addEntity(Entity entity){
	std::cout << "Entity " << nEntities << " registered" << std::endl;
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
	// std::cout << "Model " << modelNames[key] << std::endl;
	return models + modelNames[key];
}

unsigned int Resources::getShader(unsigned int i){
	return shaders[i];
}

unsigned int Resources::getShader(std::string key){
	return shaders[shaderNames[key]];
}

Camera *Resources::getCamera(){
	return &camera;
}

GLFWwindow *Resources::getWindow(){
	return window;
}

// Set

void Resources::setCamera(Camera camera){
	this->camera = camera;
}

void Resources::setWindow(GLFWwindow *window){
	this->window = window;
}

unsigned int Resources::addModel(Model model, std::string name){
	// std::cout << "Model " << name << " has been registered" << std::endl;
	models[nModels] = model;
	modelNames[name] = nModels;
	return nModels++;
}

unsigned int Resources::addShader(unsigned int shader, std::string name){
	// std::cout << "Shader " << name << " has been registered" << std::endl;
	shaders[nShaders] = shader;
	shaderNames[name] = nShaders;
	return nShaders++;
}

unsigned int Resources::addSkyBox(SkyBox skybox, std::string name) {
	skyBoxes[nSkyBoxes] = skybox;
	skyBoxNames[name] = nSkyBoxes;
	return nSkyBoxes++;
}




