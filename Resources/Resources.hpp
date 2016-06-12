#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include "Model.hpp"
#include "Entity.hpp"
#include "Camera.hpp"
#include "ParticleSystem.hpp"
#include "SkyBox.hpp"
#include "Plane.hpp"

#include <string>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Resources{
public:
	Resources(unsigned int maxEntities, unsigned int maxParticleSystems, 
		unsigned int maxModels, unsigned int maxShaders, 
		unsigned int maxSkyboxes, unsigned int maxPlanes);
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
	SkyBox *getSkyBox(std::string key);
	Plane *getPlane(std::string key);
	unsigned int getShader(unsigned int i);
	unsigned int getShader(std::string key);

	Camera *getCamera();
	GLFWwindow *getWindow();

	// Set
	void setCamera(Camera camera);
	void setWindow(GLFWwindow *window);
	unsigned int addModel(Model model, std::string name);
	unsigned int addShader(unsigned int shader, std::string name);
	unsigned int addSkyBox(SkyBox skybox, std::string name);
	unsigned int addPlane(Plane plane, std::string name);
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
	unsigned int nSkyBoxes;
	SkyBox *skyBoxes;
	std::map<std::string, unsigned int> skyBoxNames;
	unsigned int nPlanes;
	Plane *planes;
	std::map<std::string, unsigned int> planeNames;

	Camera camera;	
};

#endif