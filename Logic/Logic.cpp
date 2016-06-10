#include "Resources.hpp"
#include "Logic.hpp"
#include "Camera.hpp"
#include "Model.hpp"

#include <iostream>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

Logic::Logic(Resources *resources){
	this->resources = resources;
	window = resources->getWindow();
	std::cout << "Logic instantiated" << std::endl;
}

void Logic::update(){
	updateInputEvents();
	updateGameState();
}

void Logic::updateInputEvents(){
	glfwPollEvents();
}

void Logic::updateGameState(){

}

// Input callback functions

void Logic::loadInitialGameState(){
	loadCamera();
	loadCharacter();
	loadSkyBox();
}

void Logic::loadCharacter(){
	Model *model = resources->getModel("Wavecraft2");
	character = resources->addEntity(Entity(model));
	model = resources->getModel("star");
	unsigned int star = resources->addEntity(Entity(model));

	// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// glm::mat4 view = camera->getView();
	// glm::mat4 persp = camera->getProjection();
	// resources->getModel(0)->render(persp, glm::mat4(1.0f), view);
	// glFlush();
	// glfwSwapBuffers(window);
	// glfwPollEvents();
}

void Logic::loadCamera(){
	camera = resources->getCamera();
	camera->reposition(glm::vec3(0.0f, 2.0f, 50.0f));
	camera->lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Logic::loadSkyBox() {
	SkyBox *skyBoxModel = resources->getSkyBox("Spacebox2");
	unsigned int skx = resources->addEntity(Entity(skyBoxModel));
	Entity *skybox = resources->getEntity(skx);
	skybox->resize(2.0f);
	skybox->reposition(0.0f, 2.0f, 50.0f);
}
