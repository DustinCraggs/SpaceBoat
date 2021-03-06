#include "Resources.hpp"

#include "Model.hpp"
#include "Entity.hpp"
#include "Camera.hpp"
#include "ParticleSystem.hpp"
#include "SkyBox.hpp"
#include "Plane.hpp"

#include <iostream>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// TODO: Error checking for exceeding bounds of containers
#define N_TRANS_ENT 1

Resources::Resources(unsigned int maxEntities, unsigned int maxParticleSystems, 
					unsigned int maxModels, unsigned int maxShaders,
					unsigned int maxSkyBoxes, unsigned int maxPlanes){
	t1 = 0;
	t2 = 0;
	delta = 0;
	nEntities = 0;
	nTransparentEntities = 0;
	nParticleSystems = 0;
	nModels = 0;
	nShaders = 0;
	nSkyBoxes = 0;
	m_hasSkybox = false;
	nPlanes = 0;
	entities = new Entity[maxEntities];
	transparentEntities = new Entity[N_TRANS_ENT];
	particleSystems = new ParticleSystem[maxParticleSystems];
	models = new Model[maxModels];
	shaders = new unsigned int[maxShaders];
	skyBoxes = new SkyBox[maxSkyBoxes];
	planes = new Plane[maxPlanes];
	std::cout << "Resources instantiated" << std::endl;
}

// Time

void Resources::setCurrentTime(double t){
	t1 = t2;
	t2 = t;
	delta = t2 - t1;
}

double Resources::getCurrentTime(){
	return t2;
}

double Resources::getTimeDelta(){
	return delta;
}


// Logic
// Get

bool Resources::hasSkybox(){
	return m_hasSkybox;
}

Entity *Resources::getCurrentSkybox(){
	return &currentSkybox;
}

unsigned int Resources::entitySize(){
	return nEntities;
}

Entity *Resources::getEntityData(){
	return entities;
}

Entity *Resources::getEntity(unsigned int i){
	return entities+i;
}

unsigned int Resources::transparentEntitySize(){
	return nTransparentEntities;
}

Entity *Resources::getTransparentEntityData(){
	return transparentEntities;
}

Entity *Resources::getTransparentEntity(unsigned int i){
	return transparentEntities + i;
}

float Resources::getZFarPlane() {
	return camera.getFarClippingPlane();
}

// Set

Entity *Resources::setCurrentSkybox(Entity skybox){
	currentSkybox = skybox;
	m_hasSkybox = true;
	return &currentSkybox;
}

unsigned int Resources::addEntity(Entity entity){
	entities[nEntities] = entity;
	return nEntities++;
}

unsigned int Resources::addTransparentEntity(Entity entity){
	transparentEntities[nTransparentEntities] = entity;
	return nTransparentEntities++;
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

SkyBox* Resources::getSkyBox(std::string key) {
	return skyBoxes + skyBoxNames[key];
}

Plane* Resources::getPlane(std::string key) {
	return planes + planeNames[key];
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
	models[nModels] = model;
	modelNames[name] = nModels;
	return nModels++;
}

unsigned int Resources::addShader(unsigned int shader, std::string name){
	shaders[nShaders] = shader;
	shaderNames[name] = nShaders;
	return nShaders++;
}

unsigned int Resources::addSkyBox(SkyBox skybox, std::string name) {
	std::cout << name << std::endl;
	skyBoxes[nSkyBoxes] = skybox;
	skyBoxNames[name] = nSkyBoxes;
	return nSkyBoxes++;
}

unsigned int Resources::addPlane(Plane plane, std::string name) {
	std::cout << name << std::endl;
	planes[nPlanes] = plane;
	planeNames[name] = nPlanes;
	return nPlanes++;
}

// Physics/Logic

void Resources::registerCharacter(unsigned int character){
	this->character = character;
}

void Resources::registerTrack(unsigned int track){
	this->track = track;
}

void Resources::registerAsteroid(unsigned int asteroid){
	asteroids.push_back(asteroid);
}

Entity *Resources::getCharacterPointer(){
	return entities + character;
}

Entity *Resources::getTrackPointer(){
	return transparentEntities + track;
}

std::vector<unsigned int> &Resources::getAsteroidIndices(){
	return asteroids;
}























