

class ParticleRenderer{
	// Camera *camera;
	unsigned int vao;
	unsigned int shader;
	unsigned int positionBuffer;
	unsigned int colourBuffer;
	int maxParticles;
public:
	// ParticleRenderer(){}
	void initialise(int maxParticles = 10000);
	// void initialise(int maxParticles, unsigned int shader);
	// void render(float *positions, float *colours, int n);
	void render(float *positions, float *colours, int n, unsigned int shader);
	void upload(float *positions, float *colours, int n);
};