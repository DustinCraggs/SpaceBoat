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
	openWindow(1200, 800);
	particleRenderer.initialise(5000);
	std::cout << "Graphics instantiated" << std::endl;
}


// Loading stuff

void Graphics::loadGraphicsData(std::string directory){
	loadShaders(directory + "Shaders/");
	loadModels(directory + "Models/");
	loadSkyBoxes(directory + "SkyBoxes/");
}

void Graphics::loadModels(std::string directory){
	std::cout << "Loading models from " << directory << std::endl;
	// Get names of contents of directory (might break stuff sometimes maybe)
	std::vector<std::string> files;
	tinydir_dir dir;
	tinydir_open(&dir, directory.c_str());
	while( dir.has_next ){
		tinydir_file file;
		tinydir_readfile(&dir, &file);
		if( !file.is_dir && strcmp(file.extension, "obj") == 0 ){
			std::cout << "Found model " << file.name << std::endl;
			files.push_back(file.name);
		}
		tinydir_next(&dir);
	}
	tinydir_close(&dir);

	// unsigned int shader = resources->getShader("debug_normal");
	unsigned int shader = resources->getShader("texture");
	for( int i=0; i<files.size(); i++ ){
		std::string fileName(files[i]);
		std::cout << "Adding model " << fileName << std::endl;
		resources->addModel(Model(directory+files[i], shader), fileName.substr(0, files[i].size()-4));
	}
}

void Graphics::loadSkyBoxes(std::string directory) {
	std::cout << "Loading SkyBox" << std::endl;
	// Get names of nested skybox directories
	std::vector<std::string> directories;	
	tinydir_dir dir;
	tinydir_open(&dir, directory.c_str());
	while(dir.has_next) {
		tinydir_file file;
		tinydir_readfile(&dir, &file);
		if(file.is_dir && file.name[0] != '.') {
			std::cout << "Found directory: " << file.name << std::endl;
			directories.push_back(file.name);
		}
		tinydir_next(&dir);
	}
	tinydir_close(&dir);
	unsigned int shader = resources->getShader("cubemap");
	for(int i=0; i<directories.size(); i++) {
		std::string fileName(directories.at(i));
		std::cout << "Adding skybox " << fileName << std::endl;
		resources->addSkyBox(SkyBox(directory+directories[i], shader), fileName);
	}
}


void Graphics::loadShaders(std::string directory){
	std::cout << "Loading shaders" << std::endl;
	std::vector<std::string> files;
	tinydir_dir dir;
	tinydir_open(&dir, directory.c_str());
	while( dir.has_next ){
		tinydir_file file;
		tinydir_readfile(&dir, &file);
		if( !file.is_dir && strcmp(file.extension, "vert") == 0 ){
			std::cout << "Found shader " << file.name << std::endl;
			files.push_back(file.name);
		}
		tinydir_next(&dir);
	}
	tinydir_close(&dir);

	for( int i=0; i<files.size(); i++ ){
		std::string fileName(files[i]);
		std::string name = fileName.substr(0, files[i].size()-5);
		std::cout << "Adding shader " << fileName << std::endl;
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

	glewExperimental = true;
	if( glewInit() != GLEW_OK ){
		fprintf(stderr, "GLEW initialisation failed\n");
		exit(1);
	}

	// GL
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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

	// Skybox
	if( resources->hasSkybox() ){
		renderSkybox(projection, camera->getOrientationMatrix());
	}

	// Entities
	renderEntities(projection, view);
	renderTransparentEntities(projection, view);

	// Particles
	renderParticleSystems(projection, view);

	// UI
	renderUserInterface();

	glFlush();
	glfwSwapBuffers(window);
	// glfwPollEvents();
}

void Graphics::renderSkybox(glm::mat4 projection, glm::mat4 camOrientation){
	resources->getCurrentSkybox()->render(projection, camOrientation);
}

void Graphics::renderEntities(glm::mat4 projection, glm::mat4 view){
	Entity *entities = resources->getEntityData();
	for( int i=0; i<resources->entitySize(); i++ ){
		(entities+i)->render(projection, view);
	}
}

void Graphics::renderTransparentEntities(glm::mat4 projection, glm::mat4 view){
	glDepthMask(false);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Entity *transparentEntities = resources->getTransparentEntityData();
	for( int i=0; i<resources->transparentEntitySize(); i++ ){
		(transparentEntities+i)->render(projection, view);
	}
	glDepthMask(true);
	glDisable(GL_BLEND);
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

















