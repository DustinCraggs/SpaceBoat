#include "Resources.hpp"
#include "Logic.hpp"
#include "Camera.hpp"
#include "Model.hpp"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GLFW/glfw3.h>

#include <chrono>
#include <random>

// #include <irrKlang.h>


#define NUMBER_OF_ASTEROIDS 10
#define TEST true

Logic::Logic(Resources *resources){
	this->resources = resources;
	window = resources->getWindow();
	leftMouseDown = false;
	cameraLocked = true;
}

void Logic::update(){
	std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
	double t = std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count()/(double)pow(10,9);
	resources->setCurrentTime(t);
	updateInputEvents();
	updateGameState();
}

void Logic::updateInputEvents(){
	glfwPollEvents();
}

void Logic::updateGameState(){
	// resources->getEntity(character)->move(glm::vec3(0.0f, 0.0f, 0.1f));
	// camera->move(glm::vec3(0.0f, 0.0f, 0.1f));
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
			case GLFW_KEY_UP:
	           	// logic->camera->move(glm::vec3(0.0f, 0.0f, 1.0f));
            break;
            case GLFW_KEY_LEFT:
            case GLFW_KEY_A:
            	logic->resources->charXAcceleration = 1;
            break;
            case GLFW_KEY_RIGHT:
            case GLFW_KEY_D:
            	logic->resources->charXAcceleration = -1;
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
	loadCamera();
	loadCharacter();
	loadSkyBox();
	loadTrack();
	loadRandomAsteroids();
	glfwSetWindowUserPointer(window, this);
	registerCallbacks();
	t0 = std::chrono::system_clock::now();
}

void Logic::loadCharacter(){
	unsigned int starShader = resources->getShader("debug_normal");
	Model *model1 = resources->getModel("star");
	model1->changeShader(starShader);
	unsigned int star = resources->addEntity(Entity(model1));

	Model *model = resources->getModel("Wavecraft2");
	character = resources->addEntity(Entity(model));
	Entity *ent = resources->getEntity(character);
	ent->resize(0.05f);
	ent->reposition(0.0f, 0.1f, 0.0f);
	resources->registerCharacter(character);

	Entity* estar = resources->getEntity(star);
	estar->resize(0.1f);
	estar->reposition(-1.0f, 0.0f, 10.0f);
}

void Logic::loadCamera(){
	camera = resources->getCamera();
	camera->reposition(glm::vec3(0.0f, 0.1f, -2.0f));
	camera->fixedLookAt(glm::vec3(0.0f, 0.1f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	// BUG: below line causes a seg fault for some reason
	// camera->move(resources->getEntity(character)->getPosition());
}

void Logic::loadSkyBox() {
	SkyBox *skyBoxModel = resources->getSkyBox("Spacebox2");
	Entity *skybox = resources->setCurrentSkybox(Entity(skyBoxModel));
}

void Logic::loadTrack() {
	Plane *mtrack = resources->getPlane("track");
	track = resources->addTransparentEntity(Entity(mtrack));
	resources->registerTrack(track);
	Entity* eTrack = resources->getTransparentEntity(track);
	eTrack->stretch(1.0f, 0.0f, resources->getZFarPlane());
}

void Logic::randomizeAsteroidData(Entity* asteroid) {
	seed = std::chrono::system_clock::now().time_since_epoch().count();
	float zFarPlane = resources->getZFarPlane();
  	std::default_random_engine generator(seed);

  	// asteroid vertices are huge
  	std::uniform_real_distribution<float> distribution(0.01f, 0.2f);
  	asteroid->resize(distribution(generator));
  	std::uniform_real_distribution<float> distribution2(-10.0f, 10.0f);
  	asteroid->reorient(distribution2(generator),distribution2(generator),
  		distribution2(generator));

  	// positions between -zfar and +zfar
  	std::uniform_real_distribution<float> zFarDist(-zFarPlane, zFarPlane);
  	asteroid->reposition(glm::vec3(distribution2(generator), distribution2(generator), 
  		zFarDist(generator)));
}


void Logic::loadRandomAsteroids() {
	std::cout << "creating " << NUMBER_OF_ASTEROIDS << " random asteroids" << std::endl;
	for(int i=0; i<NUMBER_OF_ASTEROIDS; i++) {
		Model* mAsteroid = resources->getModel("asteroid");
		unsigned int asteroid = resources->addEntity(Entity(mAsteroid));
		resources->registerAsteroid(asteroid);
		Entity *eAsteroid = resources->getEntity(asteroid);
		randomizeAsteroidData(eAsteroid);	
	}

}


