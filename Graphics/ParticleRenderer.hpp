#ifndef PARTICLE_RENDERER_H
#define PARTICLE_RENDERER_H

class ParticleRenderer{
	// Camera *camera;
	unsigned int vao;
	unsigned int positionBuffer;
	unsigned int colourBuffer;
	int maxParticles;
public:
	// ParticleRenderer(){}
	void initialise(unsigned int maxParticles = 10000);
	void render(float *positions, float *colours, int n, unsigned int shaderPID);
	void upload(float *positions, float *colours, int n);
};

#endif