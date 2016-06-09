#include <random>

#include "ParticleSystem.hpp"

class Physics{
public:
	Physics(float aspect, float initialIntensity);
	void nextFrame(float time, float intensity);

	// TESTING
	unsigned int nParticles();
	float *particleData();
	float *colourData();
private:
	// Data
	ParticleSystem particles;

	std::default_random_engine generator;
	std::uniform_real_distribution<float> x_distribution;
	std::uniform_real_distribution<float> y_distribution;
	std::normal_distribution<float> gen_distribution;

	// Initialisation
	void generateInitialState(float intensity);

	// 3-phase update
	void update(float time);
	void collide();
	void generate(float time, float intensity);

	float nextXCoord();
	float nextYCoord();
	float nextParticleNumber();


};