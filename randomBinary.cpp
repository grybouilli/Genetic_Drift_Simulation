#include <random>

int randomBinary() {
	
	std::random_device rd {};
	
	const int& bucket = RAND_MAX / 2;
	
	int r = rd();
	
	do r = rd() / bucket;
	while(r < 0 || r >= 2);
	
	return r;	
}