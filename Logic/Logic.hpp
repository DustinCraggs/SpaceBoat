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

	// Callbacks
	void registerCallbacks();
	static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void click_callback(GLFWwindow *window, int button, int action, int mods);
	static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
	static void window_resize_callback(GLFWwindow *window, int x, int y);

	// Keeping track of entities
	unsigned int character;
};

#endif