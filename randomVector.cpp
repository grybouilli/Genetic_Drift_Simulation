#include <Headers/randomFloat.hpp>
#include <SFML/System/Vector2.hpp>


sf::Vector2f random2D(float minX, float minY, float maxX, float maxY){
	
	return sf::Vector2f(randomFloat(minX, maxX), randomFloat(minY,maxY));
}

sf::Vector2f random2D(float min, float max) {
	
	return sf::Vector2f(randomFloat(min, max), randomFloat(min,max));
}