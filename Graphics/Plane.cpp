#include "Plane.hpp"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GL/glew.h>

#define VALS_PER_TRI 3
#define VALS_PER_VERT 3
#define TRIS_PER_FACE 2

Plane::Plane() {
}

Plane::Plane(unsigned int shader) {
	shaders.push_back(shader);
	genVao();
}

// horizontal plane
void Plane::genVao() {
	// clockwise from top left
	GLfloat planeVertices[] = {
		-1.0f, 0.0f, 1.0f, 				// Top left
		1.0f, 0.0f, 1.0f,				// Top right
		1.0f, 0.0f, -1.0f,				// Bottom right
		-1.0f, 0.0f, -1.0f				// Bottom left
	};

	GLuint indices[] = {
		0, 1, 2, 
		0, 2, 3
	};

	// Normals of each vertex
    float planeNormals[] = {
        1.0f, 1.0f, 1.0f ,
        1.0f, 1.0f, 1.0f ,
        1.0f, 1.0f, 1.0f ,
        1.0f, 1.0f, 1.0f
	};

	unsigned int vaoHandle;
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);

	unsigned int buffer[3];
	glGenBuffers(3, buffer);

	// vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, 
		GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, VALS_PER_VERT, GL_FLOAT, GL_FALSE, 0, 0);

	// Normal attributes
	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeNormals), planeNormals, 
		GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, VALS_PER_VERT, GL_FLOAT, GL_FALSE, 0, 0);

	// index attributes
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, 
		GL_STATIC_DRAW);	

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	vaos.push_back(vaoHandle);
}

void Plane::render(glm::mat4 projection, glm::mat4 model, glm::mat4 view) {
	unsigned int PID = shaders.at(0);
    glUseProgram(PID);

    glm::mat4 modelview = view * model;

    // Load transformation matrices
    GLint viewHandle = glGetUniformLocation(PID, "view_matrix");
    glUniformMatrix4fv(viewHandle, 1, GL_FALSE, glm::value_ptr(view));

    GLint modelViewHandle = glGetUniformLocation(PID, "modelview_matrix");
    glUniformMatrix4fv(modelViewHandle, 1, GL_FALSE, glm::value_ptr(modelview));

    GLint projectionHandle = glGetUniformLocation(PID, "projection_matrix");
    glUniformMatrix4fv(projectionHandle, 1, GL_FALSE, glm::value_ptr(projection));

    glEnable(GL_BLEND);
    //glDisable(GL_DEPTH_TEST);
    glBindVertexArray(vaos[0]);
    glDrawElements(GL_TRIANGLES, TRIS_PER_FACE * VALS_PER_VERT, 
    	GL_UNSIGNED_INT, 0);
    //glEnable(GL_DEPTH_TEST);
    //glDisable(GL_BLEND);
}