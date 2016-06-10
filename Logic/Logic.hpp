#ifndef LOGIC_H
#define LOGIC_H

// Logic should compute time at start of next frame commit that to Resources
// for use by other sub-systems

#include "Resources.hpp"
#include "Entity.hpp"

#include <GLFW/glfw3.h>

class Logic{
public:
	Logic(Resources *resources);
	void update();

	void loadInitialGameState();
private:
	void updateInputEvents();
	void updateGameState();

	// Loading stuff
	void loadCharacter();
	void loadCamera();
	void loadSkyBox();
	Resources *resources;
	Camera *camera;
	GLFWwindow *window;

	// Keeping track of entities
	unsigned int character;
};

#endif