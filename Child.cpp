#include "Headers/Child.hpp"
#include "Headers/Female.hpp"
#include "Headers/Male.hpp"
#include <iostream>

Child_E::Child_E()
: Elephant_Base()
, mPtr(nullptr) {
	
}


Child_E::Child_E(TextureHolder& text, std::pair<Elephant_Base::Gene, Elephant_Base::Gene> g, age_value a)
: Elephant_Base(text, Traits::sexOf(g), Traits::hasTusks(g), a)
, mPtr(nullptr) {
	
	switch(getTraits().sex) {
		
		case Female:
			mPtr = new Female_E(text, getTraits().tusks, a);
			break;
			
		case Male:
			mPtr = new Male_E(text, getTraits().tusks, a);
			break;
	}
	
}

void Child_E::update(sf::Time dt) {
	
	toAge(dt);
}

Elephant_Base::Ptr Child_E::getData() const { 
	
	return mPtr; 
}

void Child_E::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	
	states.transform *= getTransform();
	states.transform.scale(0.8f, 0.8f);
	target.draw(*mPtr, states);
	
}

