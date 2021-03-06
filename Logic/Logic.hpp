#ifndef LOGIC_H
#define LOGIC_H

// Logic should compute time at start of next frame commit that to Resources
// for use by other sub-systems

#include "Resources.hpp"
#include "Entity.hpp"

#include <GLFW/glfw3.h>
#include <chrono>

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
	void loadTrack();
	void loadSkyBox();
	void randomizeAsteroidData(Entity* asteroid);
	void loadRandomAsteroids();
	Resources *resources;

	// Time
	std::chrono::system_clock::time_point t0;

	// Camera stuff
	Camera *camera;
	double xprev, yprev;
	bool cameraLocked;
	bool leftMouseDown;
	
	GLFWwindow *window;

	// Callbacks
	void registerCallbacks();
	static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void click_callback(GLFWwindow *window, int button, int action, int mods);
	static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
	static void window_resize_callback(GLFWwindow *window, int x, int y);

	// Keeping track of entities
	unsigned int character;
	unsigned int track;
	unsigned seed;
	std::vector<unsigned int> asteroids;
};

#endif