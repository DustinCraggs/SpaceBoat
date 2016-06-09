#include "CubeMapTexture.hpp"

#include "stb_image.h"

#include <util.h>
#include <GL/glew.h>
#include <string>
#include <iostream>

using namespace std;

#define CUBE_NUM_FACES 6

static const GLenum types[6] = {
	GL_TEXTURE_CUBE_MAP_POSITIVE_X,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
   	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 
};

CubeMapTexture::CubeMapTexture(const string& directory, 
		const string& posXFilename, const string& negXFilename, 
		const string& posYFilename, const string& negYFilename, 
		const string& posZFilename, const string& negZFilename) {

	string::const_iterator it = directory.end();
	it--;
	string baseDir = (*it == '/') ? directory : directory + "/";
	filenames[0] = (baseDir + posXFilename);
	filenames[1] = baseDir + negXFilename;
	filenames[2] = baseDir + posYFilename;
	filenames[3] = baseDir + negYFilename;
	filenames[4] = baseDir + posZFilename;
	filenames[5] = baseDir + negZFilename;
	textureID = 0;

	for(int i=0; i<CUBE_NUM_FACES; i++) {
		cout << "face " << i << " loaded texture: " << filenames[i] << endl;
	}
}

CubeMapTexture::~CubeMapTexture() {
	if(textureID != 0) {
		glDeleteTextures(1, &textureID);
	}
}

bool CubeMapTexture::load() {
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	int x, y, n;
	unsigned char* data;
	for(int i=0; i<CUBE_NUM_FACES; i++) {
		cout << filenames[i] << endl;
		data = stbi_load(filenames[i].c_str(), &x, &y, &n, 3);
		glTexImage2D(types[i], 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, 
			data);
		stbi_image_free(data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE); 

	return true;
}

void CubeMapTexture::bind(GLenum textureUnit) {
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
}