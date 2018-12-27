#ifndef GUARD_WORLD_HPP
#define GUARD_WORLD_HPP

#include "Elephant_Base.hpp"
#include "Female.hpp"
#include "Male.hpp"
#include "TextureHolder.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <vector>

class World : public sf::Drawable, public sf::Transformable {
public:
	explicit 				World(sf::FloatRect worldSz, TextureHolder& textures);
	
	
	void 					generateWorld(unsigned int nbOfFemale, unsigned int nbOfMale);
	void 					update(sf::Time dt);
	
private:
	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
private:
	sf::FloatRect			mWorldSize;
	TextureHolder*			mTextures;
	sf::Sprite				mBackground;
	
	std::vector<Female_E>	mFemales;
	std::vector<Male_E>		mMales;
};

#endif