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
void Logic::registerCallbacks(){
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, click_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetFramebufferSizeCallback(window, window_resize_callback);
}

void Logic::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods){
	Logic *logic = static_cast<Logic *>(glfwGetWindowUserPointer(window));
	if( action == GLFW_PRESS || action == GLFW_REPEAT ){
		switch( key ){
			case GLFW_KEY_Z:
				// Zoom
			break;
		}
		// camera.move(0.1f * direction);
	}
}

void Logic::click_callback(GLFWwindow *window, int button, int action, int mods){
	Logic *logic = static_cast<Logic *>(glfwGetWindowUserPointer(window));
	// if( button == GLFW_MOUSE_BUTTON_LEFT && !rightMouseDown){
	// 	if( action == GLFW_PRESS ){
	// 		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// 		glfwGetCursorPos(window, &xprev, &yprev);
	// 		leftMouseDown = true;
	// 	}else if( action == GLFW_RELEASE ){
	// 		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	// 		leftMouseDown = false;
	// 	}
	// }else if( button == GLFW_MOUSE_BUTTON_RIGHT && !leftMouseDown ){
	// 	if( action == GLFW_PRESS ){
	// 		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// 		glfwGetCursorPos(window, &xprev, &yprev);
	// 		rightMouseDown = true;
	// 	}else if( action == GLFW_RELEASE ){
	// 		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	// 		rightMouseDown = false;
	// 	}
	// }
}

void Logic::cursor_position_callback(GLFWwindow *window, double xpos, double ypos){
	Logic *logic = static_cast<Logic *>(glfwGetWindowUserPointer(window));
	
}

void Logic::window_resize_callback(GLFWwindow *window, int x, int y){
	Logic *logic = static_cast<Logic *>(glfwGetWindowUserPointer(window));
	logic->camera->setWindowSize(x, y);
}


void Logic::loadInitialGameState(){
	loadCamera();
	loadCharacter();

	glfwSetWindowUserPointer(window, this);
	registerCallbacks();
}
	
void Logic::loadCharacter(){
	Model *model = resources->getModel("Wavecraft2");
	character = resources->addEntity(Entity(model));
	model = resources->getModel("star");
	unsigned int star = resources->addEntity(Entity(model));

}

void Logic::loadCamera(){
	camera = resources->getCamera();
	camera->reposition(glm::vec3(0.0f, 2.0f, 50.0f));
	camera->lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}