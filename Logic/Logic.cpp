#include "Resources.hpp"
#include "Logic.hpp"
#include "Camera.hpp"

Logic::Logic(Resources *resources){
	this->resources = resources;
	window = resources->getWindow();
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
	loadCharacter();
}

void Logic::loadCharacter(){

}

void Logic::loadCamera(){
	// resources.setCamera(Camera());
}