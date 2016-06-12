#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include "Model.hpp"
#include "Entity.hpp"
#include "Camera.hpp"
#include "ParticleSystem.hpp"
#include "SkyBox.hpp"

#include <string>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Resources{
public:
	Resources(unsigned int maxEntities, unsigned int maxParticleSystems, 
		unsigned int maxModels, unsigned int maxShaders, unsigned int maxSkyboxes);
	// Logic
	// Get
	bool hasSkybox();
	Entity *getCurrentSkybox();
	unsigned int entitySize();
	Entity *getEntityData();
	Entity *getEntity(unsigned int i);
	unsigned int transparentEntitySize();
	Entity *getTransparentEntityData();
	Entity *getTransparentEntity(unsigned int i);
	
	// Set
	Entity *setCurrentSkybox(Entity entity);
	unsigned int addEntity(Entity entity);
	unsigned int addTransparentEntity(Entity entity);

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
private:
	float dt;
	// Logic
	bool m_hasSkybox;
	Entity currentSkybox;

	unsigned int nEntities;
	Entity *entities;
	unsigned int nTransparentEntities;
	Entity *transparentEntities;

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

	Camera camera;
};

#endif