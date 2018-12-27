#include "Headers/World.hpp"
#include "Headers/randomVector.hpp"
#include "Headers/randomBinary.hpp"
#include <iostream>
#include <algorithm>

World::World(sf::FloatRect worldSz, TextureHolder& textures)
: mWorldSize(worldSz)
, mTextures(&textures)
, mBackground() {
	
}

void World::generateWorld(unsigned int nbOfFemale, unsigned int nbOfMale) {
	
	//generating female elephants
	for(unsigned int i = 0; i != nbOfFemale; ++i) {
		
		mFemales.push_back(Female_E(*mTextures, static_cast<bool>(randomBinary()), 20));
		mFemales[i].setPosition(random2D(mWorldSize.left, mWorldSize.top, mWorldSize.width, mWorldSize.height));
		mFemales[i].setEnclosure(sf::FloatRect(mWorldSize.left, mWorldSize.height / 2, mWorldSize.width, mWorldSize.height));
	}
	
	//generating male elephants
	for(unsigned int j = 0; j != nbOfMale; ++j) {
		
		Male_E elephant(Male_E(*mTextures, static_cast<bool>(randomBinary()), 20));
		elephant.setPosition(random2D(mWorldSize.left, mWorldSize.top, mWorldSize.width, mWorldSize.height));
		elephant.setEnclosure(sf::FloatRect(mWorldSize.left, mWorldSize.height / 2, mWorldSize.width, mWorldSize.height));
		mMales.push_back(elephant);
	}
	
	mBackground.setTexture(mTextures->get(Texture::Background));
	sf::IntRect textureSize(mBackground.getTextureRect());
	mBackground.scale(mWorldSize.width / textureSize.width, mWorldSize.height / textureSize.height);
}

void World::update(sf::Time dt) {
	
	//females update
	for(auto i = 0; i != mFemales.size(); ++i) {
		//update current female
		mFemales[i].update(dt);
		
		//if current female's child is old enough to become adult, we make a new elephant with its traits
		if(mFemales[i].hasChildGrown()) {
			
			Elephant_Base::Ptr child = mFemales[i].detachChild();
			
			switch(child->getTraits().sex){
				case Elephant_Base::Sex::Female:
					mFemales.push_back(Female_E(*mTextures, child->getTraits().tusks, 
					child->getTraits().age));
					mFemales[mFemales.size()-1].setPosition(mFemales[i].getPosition());
					mFemales[mFemales.size()-1].setEnclosure(mFemales[i].getEnclosure());
					break;
				
				case Elephant_Base::Sex::Male:
					mMales.push_back(Male_E(*mTextures, child->getTraits().tusks, 
					child->getTraits().age));
					mMales[mMales.size()-1].setPosition(mFemales[i].getPosition());
					mMales[mMales.size()-1].setEnclosure(mFemales[i].getEnclosure());
					break;
			}
		}
	}
	
	//males update
	for(auto j = 0; j != mMales.size(); ++j) {
		
		mMales[j].update(dt);
		
		//checks if current Male_E can mate with any of the Female_E
		for(auto k = 0; k != mFemales.size(); ++k) {
			
			if(mMales[j].isMeeting(mFemales[k]))
				mMales[j].tryToMate(mFemales[k]);
		}
				
	}
	
	//erases dead elephants
	mFemales.erase(std::remove_if(mFemales.begin(), mFemales.end(), 
	[](Female_E e) { return !e.isAlive(); }),
	mFemales.end());
	
	mMales.erase(std::remove_if(mMales.begin(), mMales.end(), 
	[](Male_E e) { return !e.isAlive(); }), 
	mMales.end());
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	states.transform *= getTransform();
	target.draw(mBackground, states);
	
	for(unsigned int i = 0; i != mFemales.size(); ++i) {
		
		target.draw(mFemales[i], states); 
	}
	
	for(unsigned int j = 0; j != mMales.size(); ++j) {
		
		target.draw(mMales[j], states);
	}
}