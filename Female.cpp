#include "Headers/Female.hpp"
#include "Headers/Male.hpp"
#include <cmath>
#include <utility>
#include <iostream>
#include <memory>
#include <SFML/Graphics/RenderTarget.hpp>

/* constructors: */ 

Female_E::Female_E()
: Elephant_Base()
, mChild()
, mIsPregnant(false)
, mGestationTime(0.f) {
	
}

Female_E::Female_E(TextureHolder& text, bool hasTusks, age_value a)
: Elephant_Base(text, Elephant_Base::Sex::Female, hasTusks, a)
, mChild()
, mIsPregnant(false)
, mGestationTime(0.f) {
	
	if(getTraits().tusks)
		mShape.setTexture(getTraits().textures->get(Texture::TuskedFemale));
	else
		mShape.setTexture(getTraits().textures->get(Texture::UntuskedFemale));
}


/* public methods : */

void Female_E::update(sf::Time dt) {
	
	//if elephant is dead, no need to go further
	if(!isAlive())
		return;
		
	updateMovement(dt);
	toAge(dt);
	
	if(mIsPregnant) {
		
		mGestationTime += dt.asSeconds() / Elephant_Base::YEAR_IN_SECONDS_VALUE.asSeconds();
		if(mGestationTime > 1.75f) {
			//if gestation comes to term, give birth
			giveBirth();
			
		}
	} else if(mChild) {
		//if not pregnant any more, it may now have a child to update
		mChild.update(dt);
	}
	
}

bool Female_E::canGetPregnant() const {
	
	if(mChild || mIsPregnant || getTraits().age > 50 || getTraits().age < 25)
		return false;
		
	else
		return true;
}

bool Female_E::hasChildGrown() const {
	
	if(mChild.getTraits().age > 4)
		return true;
		
	else
		return false;
}

Elephant_Base::Ptr Female_E::detachChild() {
	
	Child_E ret = mChild;
	mChild = Child_E();
	
	return ret.getData();
}

bool Female_E::isPregnant() const {
	return mIsPregnant; 
}

/* private methods : */

void Female_E::makePregnant(const Elephant_Base::Gene& maleGamete) {
	
	if(!canGetPregnant())
		return;
		
	mChild = Child_E(*getTraits().textures, std::make_pair(generateGametes(), maleGamete));
	mIsPregnant = true;
}

void Female_E::giveBirth() {
	
	std::cout << "giving birth" << std::endl;
	mIsPregnant = false;
	mGestationTime = 0.f;
	mChild.setPosition(30.f, 30.f);
}

void Female_E::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	
	states.transform *= getTransform();
	target.draw(mShape, states);
	if(mChild && !mIsPregnant)
		target.draw(mChild, states);
}