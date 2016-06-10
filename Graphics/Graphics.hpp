#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Resources.hpp"
#include "Model.hpp"
#include "Entity.hpp"
#include "ParticleRenderer.hpp"
#include "ParticleSystem.hpp"

#include "tinydir.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Graphics{
public:
	// Initialisation
	Graphics(Resources *resources);
	void loadGraphicsData(std::string directory);
	void openWindow(unsigned int xdim, unsigned int ydim);

	// Rendering
	void renderFrame();
	void renderEntities(glm::mat4 projection, glm::mat4 view);
	void renderParticleSystems(glm::mat4 projection, glm::mat4 view);
	void renderUserInterface();

	// Window
	void resizeWindow();
	bool windowShouldClose();
private:
	Resources *resources;
	GLFWwindow *window;

	ParticleRenderer particleRenderer;
	unsigned int particleShader;

	void loadModels(std::string directory);
	void loadShaders(std::string directory);
	void loadSkyBoxes(std::string directory);
	unsigned int compileShader(std::string name);
};

#endif