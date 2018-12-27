#include <random>

float randomFloat(float min, float max) {
	
	std::random_device rd{};
	
	float r{};
	
	do r = (float(rd()) / (RAND_MAX / (max - min))) + min;
	while (r < min || r > max);
	
	return r;
}