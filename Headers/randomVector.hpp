#ifndef GUARD_RANDOMVECTOR_HPP
#define GUARD_RANDOMVECTOR_HPP

#include <SFML/System/Vector2.hpp>

sf::Vector2f random2D(float minX, float minY, float maxX, float maxY);
sf::Vector2f random2D(float min, float max);

#endif