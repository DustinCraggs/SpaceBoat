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

	// Loading stuff
	void loadInitialGameState();
	void loadCharacter();
	void loadCamera();
private:
	void updateInputEvents();
	void updateGameState();

	Resources *resources;
	Camera *camera;
	GLFWwindow *window;
};

#endif