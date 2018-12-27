#include <Headers/Male.hpp>
#include <Headers/constrain.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <cmath>
#include <utility>
#include <memory>
#include <iostream>

/* constructors: */ 

Male_E::Male_E()
: Elephant_Base() {
	
}

Male_E::Male_E(TextureHolder& text, bool hasTusks, age_value a)
: Elephant_Base(text, Elephant_Base::Sex::Male, hasTusks, a) {
	
	if(getTraits().tusks)
		mShape.setTexture(getTraits().textures->get(Texture::TuskedMale));
	else
		mShape.setTexture(getTraits().textures->get(Texture::UntuskedMale));
}


/* public methods : */

void Male_E::update(sf::Time dt) {
	
	//if elephant is dead, no need to go further
	if(!isAlive())
		return;
	
	updateMovement(dt);	
	toAge(dt);
	
}

bool Male_E::isMeeting(const Female_E& f) const {
	
	return getBoundaries().intersects(f.getBoundaries());
}

void Male_E::tryToMate(Female_E& female) {
	
	if(getTraits().age < 25 || !female.canGetPregnant()) {
		
		return;
	}
		
	if(female.canGetPregnant()) {
		
		female.makePregnant(generateGametes());
	}
	
}


void Male_E::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	
	states.transform *= getTransform();
	target.draw(mShape, states);
}