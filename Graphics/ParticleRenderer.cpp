#include "ParticleRenderer.hpp"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void ParticleRenderer::initialise(unsigned int maxParticles){
	this->maxParticles = maxParticles;
	// Create initial VAO
	std::cout << "Particle Renderer: Generating VAOs" << std::endl;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::cout << "Particle Renderer: Generated VAOs" << std::endl;

	glGenBuffers(1, &positionBuffer);
	glGenBuffers(1, &colourBuffer);

	// Positions
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, 3 * maxParticles * sizeof(float), NULL, GL_STREAM_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// Colours
	glBindBuffer(GL_ARRAY_BUFFER, colourBuffer);
	glBufferData(GL_ARRAY_BUFFER, 3 * maxParticles * sizeof(float), NULL, GL_STREAM_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
}

// void ParticleRenderer::initialise(unsigned int maxParticles, unsigned int shader){
	
// }

void ParticleRenderer::render(float *positions, float *colours, int n, unsigned int shaderPID){
	glUseProgram(shaderPID);
	glBindVertexArray(vao);
	upload(positions, colours, n);
	// Render
	glDrawArrays(GL_POINTS, 0, n*3);
	glBindVertexArray(0);
}

void ParticleRenderer::upload(float *positions, float *colours, int n){
	// Rebind VAO if GL blocks and buffer new data
	// Positions
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, 3 * n * sizeof(float), NULL, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * n * sizeof(float), positions);

	// Colours
	glBindBuffer(GL_ARRAY_BUFFER, colourBuffer);
	glBufferData(GL_ARRAY_BUFFER, 3 * n * sizeof(float), NULL, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * n * sizeof(float), colours);
}