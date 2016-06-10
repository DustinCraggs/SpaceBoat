#include "Logic.hpp"
#include "Graphics.hpp"
#include "Physics.hpp"

class Control{
public:
	void startGame();
private:
	void initialiseGraphics();
	void initialiseLogic();
	void initialisePhysics();

	Resources resources;
	Graphics graphics;
	Logic logic;
	// Physics physics;
};