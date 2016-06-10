#include "Logic.hpp"
#include "Graphics.hpp"
#include "Physics.hpp"

#define WINDOW_X 1200
#define WINDOW_Y 800

#define MAX_ENTS 100
#define MAX_PART_SYSTEMS 2
#define MAX_MODELS 20

void Control::Control() : 	
	resources(MAX_ENTS, MAX_PART_SYSTEMS, MAX_MODELS),
	logic(&resources),
	graphics(&resources){

	graphics.loadGraphicsData("Assets/");
	resources.setCamera(Camera(WINDOW_X, WINDOW_Y, (float)(M_PI/4), 0.05f, 50.0f));


}

void Control::StartGame(){
	graphics.openWindow(WINDOW_X, WINDOW_Y);


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