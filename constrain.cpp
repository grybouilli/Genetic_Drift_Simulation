#include <SFML/System/Vector2.hpp>

void constrain(sf::Vector2f& vec, float min, float max) {
	
	if(vec.x < min)
		vec.x = min;
	else if(vec.x > max)
		vec.x = max;
		
	if(vec.y < min)
		vec.y = min;
	else if(vec.y > max)
		vec.y = max;
		
}