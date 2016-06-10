#include "Control.hpp"

#include "Logic.hpp"
#include "Graphics.hpp"
#include "Physics.hpp"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define WINDOW_X 1200
#define WINDOW_Y 800

#define MAX_ENTS 100
#define MAX_PART_SYSTEMS 2
#define MAX_MODELS 20
#define MAX_SHADERS 5
#define MAX_SKYBOXES 2

Control::Control() : 	
	resources(MAX_ENTS, MAX_PART_SYSTEMS, MAX_MODELS, MAX_SHADERS, MAX_SKYBOXES),
	logic(&resources),
	graphics(&resources) {
	graphics.loadGraphicsData("Assets/");
	resources.setCamera(Camera(WINDOW_X, WINDOW_Y, (float)(M_PI/4), 0.05f, 100.0f));
}

void Control::startGame(){
	// graphics.openWindow(WINDOW_X, WINDOW_Y);

	logic.loadInitialGameState();
	// Main loop
	while( !graphics.windowShouldClose() ){
		logic.update();
		// physics.update();
		graphics.renderFrame();
	}
}

// void Control::initialiseGraphics(){

// }

// void Control::initialiseLogic(){

// }

// void Control::initialisePhysics(){

// }