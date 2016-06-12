#include "Resources.hpp"
#include "Logic.hpp"
#include "Camera.hpp"
#include "Model.hpp"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GLFW/glfw3.h>
// #include <irrKlang.h>

#define TEST true

Logic::Logic(Resources *resources){
	this->resources = resources;
	window = resources->getWindow();
	leftMouseDown = false;
	cameraLocked = true;
}

void Logic::update(){
	// TODO: update dt
	
	updateInputEvents();
	updateGameState();
}

void Logic::updateInputEvents(){
	glfwWaitEvents();
}

void Logic::updateGameState(){

}

// Input callback functions
void Logic::registerCallbacks(){
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, click_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetFramebufferSizeCallback(window, window_resize_callback);
}

void Logic::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods){
	Logic *logic = static_cast<Logic *>(glfwGetWindowUserPointer(window));
	Entity* craft = logic->resources->getEntity(logic->character);
    glm::vec3 orientation = craft->getOrientation();
	if( action == GLFW_PRESS || action == GLFW_REPEAT ){
		switch( key ){
			case GLFW_KEY_L:
				if( !logic->cameraLocked ){
					logic->camera->resetYOrbit();
				}
				logic->cameraLocked = !logic->cameraLocked;
			break;
		}
	}
}

void Logic::click_callback(GLFWwindow *window, int button, int action, int mods){
	Logic *logic = static_cast<Logic *>(glfwGetWindowUserPointer(window));
	if( button == GLFW_MOUSE_BUTTON_LEFT){
		if( action == GLFW_PRESS ){
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwGetCursorPos(window, &(logic->xprev), &logic->yprev);
			logic->leftMouseDown = true;
		}else if( action == GLFW_RELEASE ){
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			logic->leftMouseDown = false;
		}
	}
}

void Logic::cursor_position_callback(GLFWwindow *window, double xpos, double ypos){
	Logic *logic = static_cast<Logic *>(glfwGetWindowUserPointer(window));
	if( logic->leftMouseDown ){
		glm::vec2 windowSize = logic->camera->getWindowSize();
		double deltaX = 0;
		double deltaY = -(ypos - logic->yprev);
		if( logic->cameraLocked ){
			// double deltaY = 0;
		}else{
			deltaX = logic->xprev - xpos;
		}
		logic->camera->restrictedOrbit(2 * M_PI * deltaY/windowSize.y, 2 * M_PI * deltaX/windowSize.x);
		logic->xprev = xpos;
		logic->yprev = ypos;
	}
}

void Logic::window_resize_callback(GLFWwindow *window, int x, int y){
	Logic *logic = static_cast<Logic *>(glfwGetWindowUserPointer(window));
	logic->camera->setWindowSize(x, y);
}


void Logic::loadInitialGameState(){
	std::cout << "loading initial game state" << std::endl;
	loadCamera();
	loadCharacter();
	loadSkyBox();
	loadTrack();
	std::cout << "All game entities loaded" << std::endl;
	glfwSetWindowUserPointer(window, this);
	registerCallbacks();
}

void Logic::loadCharacter(){

	// model = resources->getModel("star");
	// unsigned int star = resources->addEntity(Entity(model));
	// Entity *ent1 = resources->getEntity(character);
	// Entity *ent2 = resources->getEntity(star);
	// ent2->rescale(0.2f, 0.2f, 0.2f);
	// ent->reposition(0.0f, 1.0f, 0.0f);
	// ent->reorient(glm::vec3(1.0f, 0.0f, 0.0f));

	unsigned int starShader = resources->getShader("debug_normal");
	Model *model1 = resources->getModel("star");
	model1->changeShader(starShader);
	unsigned int star = resources->addEntity(Entity(model1));

	
	Model *model = resources->getModel("Wavecraft2");
	character = resources->addEntity(Entity(model));
	Entity *ent = resources->getEntity(character);
	ent->rescale(2.0f, 2.0f, 2.0f);
	ent->reposition(0.0f, 1.0f, 0.0f);
	//ent->reorient(glm::vec3(0.0f, 0.0f, 1.0f));

	Entity* estar = resources->getEntity(star);
	estar->resize(0.1f);
	estar->reposition(-1.0f, 0.0f, 10.0f);
}

void Logic::loadCamera(){
	camera = resources->getCamera();
	camera->reposition(glm::vec3(0.0f, 0.0f, -20.0f));
	camera->lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Logic::loadSkyBox() {
	SkyBox *skyBoxModel = resources->getSkyBox("Spacebox5");
	Entity *skybox = resources->setCurrentSkybox(Entity(skyBoxModel));
}

void Logic::loadTrack() {
	std::cout << "loading track" << std::endl;
	Plane *mtrack = resources->getPlane("track");
	track = resources->addEntity(Entity(mtrack));
	Entity* eTrack = resources->getEntity(track); 
	eTrack->resize(100.0f);
	eTrack->reposition(0.0f, -10.0f, 0.0f);
}



