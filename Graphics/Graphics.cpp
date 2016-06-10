#include "Graphics.hpp"

#include "Resources.hpp"
#include "Model.hpp"
#include "Entity.hpp"
#include "ParticleRenderer.hpp"
#include "ParticleSystem.hpp"

// Libraries
#include "tinydir.h"
#include "shader.hpp"

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Graphics::Graphics(Resources *resources){
	this->resources = resources;
	glewExperimental = true;
	if( glewInit() != GLEW_OK ){
		fprintf(stderr, "GLEW initialisation failed\n");
		exit(1);
	}

	particleRenderer.initialise(5000);
}


// Loading stuff

void Graphics::loadGraphicsData(std::string directory){
	loadModels(directory + "/Models");
	loadShaders(directory + "/Shaders");
}

void Graphics::loadModels(std::string directory){
	// Get names of contents of directory (might break stuff sometimes maybe)
	std::vector<std::string> files;
	tinydir_dir dir;
	tinydir_open(&dir, directory.c_str());
	while( dir.has_next ){
		tinydir_file file;
		tinydir_readfile(&dir, &file);
		if( !file.is_dir && strcmp(file.extension, ".obj") == 0 ){
			files.push_back(file.name);
		}
		tinydir_next(&dir);
	}
	tinydir_close(&dir);

	for( int i=0; i<files.size(); i++ ){
		std::string fileName(files[i]);
		resources->addModel(Model(directory+files[i]), fileName.substr(0, files[i].size()-4));
	}
}

void Graphics::loadShaders(std::string directory){
	std::vector<std::string> files;
	tinydir_dir dir;
	tinydir_open(&dir, directory.c_str());
	while( dir.has_next ){
		tinydir_file file;
		tinydir_readfile(&dir, &file);
		if( !file.is_dir && strcmp(file.extension, ".vert") == 0 ){
			files.push_back(file.name);
		}
		tinydir_next(&dir);
	}
	tinydir_close(&dir);

	for( int i=0; i<files.size(); i++ ){
		std::string fileName(files[i]);
		std::string name = fileName.substr(0, files[i].size()-5);
		resources->addShader(compileShader(directory + name), name);
	}
}


unsigned int Graphics::compileShader(std::string path){
	unsigned int PID = LoadShaders((path + ".vert").c_str(), (path + ".frag").c_str());
	if( PID == 0 ){
		std::cout << "Error: Compilation of " << path << " shader failed" << std::endl;
		exit(1);
	}
	return PID;
}

void error_callback(int error, const char* description){
	fputs(description, stderr);
	fputs("\n", stderr);
}

void Graphics::openWindow(unsigned int xdim, unsigned int ydim){
	// GLFW
	glfwSetErrorCallback(error_callback);
	if( !glfwInit() ){
		exit(1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	window = glfwCreateWindow(xdim, ydim, "Assignment 3", NULL, NULL);
	resources->setWindow(window);
	if( !window ){
		glfwTerminate();
		exit(0);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// GL
	glClearColor(0.4f, 0.8f, 0.8f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glFrontFace(GL_CCW);
}

// Rendering

void Graphics::renderFrame(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Camera *camera = resources->getCamera();
	glm::mat4 projection = camera->getProjection();
	glm::mat4 view = camera->getView();

	renderEntities(projection, view);
	renderParticleSystems(projection, view);
	renderUserInterface();

	glFlush();
	glfwSwapBuffers(window);
}

void Graphics::renderEntities(glm::mat4 projection, glm::mat4 view){
	Entity *entities = resources->getEntityData();
	for( int i=0; i<resources->entitySize(); i++ ){
		(entities+i)->render(projection, view);
	}
}

void Graphics::renderParticleSystems(glm::mat4 projection, glm::mat4 view){
	ParticleSystem *particleSystem = resources->getParticleData();
	for( int i=0; i<resources->particleSystemSize(); i++ ){
		particleRenderer.render(particleSystem->getPosPointer(), particleSystem->getColPointer(), particleSystem->nParticles(), particleShader);
		particleSystem++;
	}
}

void Graphics::renderUserInterface(){
	// NYI
}

bool Graphics::windowShouldClose(){
	return glfwWindowShouldClose(window);
}

















