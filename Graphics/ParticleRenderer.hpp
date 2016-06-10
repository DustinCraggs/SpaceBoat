

class ParticleRenderer{
	// Camera *camera;
	unsigned int vao;
	unsigned int positionBuffer;
	unsigned int colourBuffer;
	int maxParticles;
public:
	// ParticleRenderer(){}
	void initialise(int maxParticles = 10000);
	void render(float *positions, float *colours, int n, unsigned int shaderPID);
	void upload(float *positions, float *colours, int n);
};