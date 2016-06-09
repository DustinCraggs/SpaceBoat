#include "Resources.hpp"

#include <string>

class Graphics{
public:
	// Initialisation
	Graphics(Resources resources);
	void loadGraphicsData(std::string directory);
	void openWindow();

	// Rendering
	void renderFrame();
	void renderEntities();
	void renderParticleSystems();
	void renderUserInterface();

	// Window
	void resizeWindow();

private:
	Resources *resources;

	// Now implemented in model
	void loadObj(std::string path);
	void loadShape();
	void loadShader();
	void loadTexture();

};

int main(){}