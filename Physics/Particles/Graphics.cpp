#include "Graphics.hpp"

#include <iostream>
#include <unistd.h>
#include <math.h>

#include "shader.hpp"

Graphics::Graphics() : physics(1, 300){
	initWindow();
	particleShader = compileShader("particle");
	particleRenderer.initialise(1000);
	// TESTING
    prev =  std::chrono::high_resolution_clock::now();
}

unsigned int Graphics::compileShader(std::string name){
	unsigned int PID = LoadShaders((name + ".vert").c_str(), (name + ".frag").c_str());
	if( PID == 0 ){
		exit(1);
	}
	return PID;
}

void Graphics::nextFrame(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(particleShader);

    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	float delta =  std::chrono::duration_cast<std::chrono::nanoseconds>(now - prev).count()/pow(10,9);
	prev = now;
	std::cout << delta << std::endl;
	physics.nextFrame(delta, 300);
	particleRenderer.render(physics.particleData(), physics.colourData(), physics.nParticles(), particleShader);

	glFlush();
	glfwSwapBuffers(window);
	glfwWaitEvents();
}

bool Graphics::shouldClose(){
	return glfwWindowShouldClose(window);
}

void Graphics::errCallback(int error, const char *description){
	fputs(description, stderr);
	fputs("\n", stderr);
}

void Graphics::initWindow(){
	std::cout << "initialisation" << std::endl;
	glfwSetErrorCallback(errCallback);

	if( !glfwInit() ){
		exit(1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	std::cout << "Window creation" << std::endl;
	window = glfwCreateWindow(1000, 800, "Particle sim", NULL, NULL);
	std::cout << "Window created" << std::endl;

	if( !window ){
		glfwTerminate();
		exit(0);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glewExperimental = true;
	if( glewInit() != GLEW_OK ){
		fprintf(stderr, "GLEW initialisation failed\n");
		exit(1);
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// glEnable(GL_DEPTH_TEST);
	glEnable(GL_PROGRAM_POINT_SIZE); 

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	// glEnable(GL_MULTISAMPLE);
	glFrontFace(GL_CCW);
}





