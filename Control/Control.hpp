// #ifndef CONTROL_H
// #define CONTROL_H

#include "Logic.hpp"
#include "Graphics.hpp"
#include "Physics.hpp"

#include <GLFW/glfw3.h>

class Control{
public:
	Control();
	void startGame();
private:
	void initialiseGraphics();
	void initialiseLogic();
	void initialisePhysics();

	Resources resources;
	Graphics graphics;
	Logic logic;
	Physics physics;
};

// #endif