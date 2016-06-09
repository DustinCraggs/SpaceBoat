#include "ParticleRenderer.hpp"
#include "Physics.hpp"

#include <iostream>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Graphics{
public:
	Graphics();
	void nextFrame();
	bool shouldClose();
private:
	GLFWwindow *window;
	// int windowSizeX, windowSizeY;
	ParticleRenderer particleRenderer;
	unsigned int particleShader;
	
	// TEST: Particles
	// int nParticles;
	// float *positions;
	// float *colours;

	void initWindow();
	unsigned int compileShader(std::string name);

	// Window callbacks
	static void errCallback(int error, const char *description);

	// Testing
	Physics physics;
	std::chrono::high_resolution_clock::time_point  prev;
};