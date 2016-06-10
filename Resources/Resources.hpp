#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include "Model.hpp"
#include "Entity.hpp"
#include "Camera.hpp"
#include "ParticleSystem.hpp"

#include <string>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Resources{
public:
	Resources(unsigned int maxEntities, unsigned int maxParticleSystems, unsigned int maxModels, unsigned int maxShaders);
	// Logic
	// Get
	unsigned int entitySize();
	Entity *getEntityData();
	Entity *getEntity(unsigned int i);
	
	// Set
	unsigned int addEntity(Entity entity);

	// Physics
	// Get
	unsigned int particleSystemSize();
	ParticleSystem *getParticleData();
	
	// Set
	unsigned int addParticleSystem(ParticleSystem particleSystem);

	// Graphics
	// Get
	unsigned int modelSize();
	Model *getModelData();
	Model *getModel(unsigned int i);
	Model *getModel(std::string key);
	unsigned int getShader(unsigned int i);
	unsigned int getShader(std::string key);

	Camera *getCamera();
	GLFWwindow *getWindow();

	// Set
	void setCamera(Camera camera);
	void setWindow(GLFWwindow *window);
	unsigned int addModel(Model model, std::string name);
	unsigned int addShader(unsigned int shader, std::string name);
private:
	float dt;
	// Logic
	unsigned int nEntities;
	Entity *entities;

	// Physics
	unsigned int nParticleSystems;
	ParticleSystem *particleSystems;
	
	// Graphics
	GLFWwindow *window;
	unsigned int nModels;
	Model *models;
	std::map<std::string, unsigned int> modelNames;
	unsigned int nShaders;
	unsigned int *shaders;
	std::map<std::string, unsigned int> shaderNames;

	Camera camera;
};

#endif