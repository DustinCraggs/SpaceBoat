#ifndef CUBEMAPTEXTURE_H
#define CUBEMAPTEXTURE_H

#include <GL/glew.h>
#include <string>

// Class to wrap the OpenGL implementation of cubemap texture and provide
// a simple interface to load and use a cubemap.
// Adapted from http://ogldev.atspace.co.uk/www/tutorial25/tutorial25.html
class CubeMapTexture {

public:
	// Constructor must take a list of filenames for each face of the cube
	CubeMapTexture(
		const std::string& directory, 
		const std::string& posXFilename,
		const std::string& negXFilename, 
		const std::string& posYFilename,
		const std::string& negYFilename, 
		const std::string& posZFilename, 
		const std::string& negZFilename);

	~CubeMapTexture();
	// Loads the provided images in the constructor into the cubemap
	bool load();

	// Bind to the cubemap for drawing
	void bind(GLenum textureUnit);
	GLuint textureID;

private:
	std::string filenames[6];

};

#endif // CUBEMAPTEXTURE_H