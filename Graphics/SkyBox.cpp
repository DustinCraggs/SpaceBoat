#define STBI_IMAGE_IMPLEMENTATION

#include "SkyBox.hpp"
#include "CubeMapTexture.hpp"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <vector>
#include <glm/ext.hpp>
#include <iostream>
using namespace std;

#define CUBE_NUM_FACES 6
#define TRIS_PER_FACE 2
#define VALS_PER_VERT 3

static const GLenum types[6] = {
	GL_TEXTURE_CUBE_MAP_POSITIVE_X,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
   	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 
};

// Default Constructor

SkyBox::SkyBox() {

}

SkyBox::SkyBox(const std::string directory, unsigned int shader) {
    vector<string> filepaths;
    filepaths = {"right.png", "left.png",
                   "top.png", "bottom.png",
                   "back.png", "front.png"};

    string::const_iterator it = directory.end();
    it--;
    string baseDir = (*it == '/') ? directory : directory + "/";
    for(int i=0; i<filepaths.size(); i++) {
        filenames[i] = baseDir + filepaths[i];
    }
    shaders.push_back(shader);
    unsigned int newTexID = loadTexture();
    textures.push_back(newTexID);
    activeTexture = 0;
	genVao();	
}

void SkyBox::render(glm::mat4 projection, glm::mat4 model, glm::mat4 view) {

    unsigned int PID = shaders.at(0);
    glUseProgram(PID);
    glDisable(GL_DEPTH_TEST);
    glm::mat4 modelview = view * model;

    // Load transformation matrices
    GLint viewHandle = glGetUniformLocation(PID, "view_matrix");
    glUniformMatrix4fv(viewHandle, 1, GL_FALSE, glm::value_ptr(view));

    GLint modelViewHandle = glGetUniformLocation(PID, "modelview_matrix");
    glUniformMatrix4fv(modelViewHandle, 1, GL_FALSE, glm::value_ptr(modelview));

    GLint projectionHandle = glGetUniformLocation(PID, "projection_matrix");
    glUniformMatrix4fv(projectionHandle, 1, GL_FALSE, glm::value_ptr(projection));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textures[activeTexture]);
    glBindVertexArray(vaos[0]);
    glDrawArrays(GL_TRIANGLES, 0, CUBE_NUM_FACES * TRIS_PER_FACE * VALS_PER_VERT);
    glEnable(GL_DEPTH_TEST);
}

// Take what is stored in the filenames array currently, and load that texture
// return the texture ID
unsigned int SkyBox::loadTexture() {
	unsigned int textureID;
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	int x, y, n;
	unsigned char* data;
	for(int i=0; i<CUBE_NUM_FACES; i++) {
		data = stbi_load(filenames[i].c_str(), &x, &y, &n, STBI_rgb);
		glTexImage2D(types[i], 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, 
			data);
		stbi_image_free(data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE); 
    return textureID;
}

// Generate the cube vao for the skybox texture
void SkyBox::genVao() {
	GLfloat cubeVertices[] = {
        -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
        1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 
        1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 
        1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 
        -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 
        -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 

        -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f,

        -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
        -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
        -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
        -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
        -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
        -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,

        1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
        1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
        1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
        1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
        1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
        1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,

        -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
        1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
        1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
        1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
        -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
        -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,

        -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f
    };

    unsigned int vaoHandle;
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);
	// Buffers to store position, colour and index data
	unsigned int buffer[2];
	glGenBuffers(2, buffer);

	// Set vertex position
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, 
                 sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, VALS_PER_VERT, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

	// Set vertex normal
	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, 
                 sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, VALS_PER_VERT, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),(GLvoid*)(3 * sizeof(GLfloat)));
    
    // Un-bind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	vaos.push_back(vaoHandle);
}
