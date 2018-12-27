#ifndef GUARD_GIVE_RANDOM_HPP
#define GUARD_GIVE_RANDOM_HPP

#include <random>

template <typename T>
T give_random(T min, T max) {
	
	std::random_device rd{};
	
	const T& bucket_size = T(RAND_MAX) / max;
	
	T r = T(rd());
	
	do r = rd() / bucket_size;
	while (r < min || r > max);
	
	return r;
}

#endif