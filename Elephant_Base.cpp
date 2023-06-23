#include "Headers/Elephant_Base.hpp"
#include "Headers/give_random.hpp"
#include "Headers/randomVector.hpp"
#include "Headers/constrain.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <cmath>
#include <utility>
#include <memory>
#include <iostream>

const sf::Time Elephant_Base::YEAR_IN_SECONDS_VALUE = sf::seconds(12.f);

/* constructors : */

Elephant_Base::Elephant_Base()
: mShape()
, mTraits()
, mMovement(0.f, 0.f)
, mEnclosure(0,0,0,0) {
	
}

Elephant_Base::Elephant_Base(TextureHolder& text, Sex sex, bool hasTusks, age_value a)
: mShape()
, mTraits(text, sex, hasTusks, a)
, mMovement(random2D(-20.f, 20.f))
, mEnclosure(0,0,1300,900) {	
	
	mShape.scale(0.1f, 0.1f);
}

Elephant_Base::Traits::Traits()
: sex(Sex::None)
, genes(std::make_pair(Gene::Undefined, Gene::Undefined))
, tusks()
, alive(false)
, age(0.f)
, textures(nullptr) {
	
}

Elephant_Base::Traits::Traits(TextureHolder& text, Sex s, bool hasTusks, age_value a)
: tusks(hasTusks)
, alive(true)
, age(a)
, textures(&text) {
	
	sex = s;
	generateGenes(s, hasTusks);
}

Elephant_Base::Traits::Traits(TextureHolder& text, std::pair<Elephant_Base::Gene, Elephant_Base::Gene> g, age_value a)
: alive(true)
, age(a)
, textures(&text) {
	
	genes = g;
	
	if(g.second == Gene::Y)
		sex = Sex::Male;
	else
		sex = Sex::Female;
		
	tusks = hasTusks(genes);
		
}

/* Traits methods : */

bool Elephant_Base::Traits::hasTusks(std::pair<Gene, Gene> g) {
	
	if(g.first == Elephant_Base::Gene::Xi || g.second == Elephant_Base::Gene::Xi)
		return true;
	else
		return false;
}

Elephant_Base::Sex Elephant_Base::Traits::sexOf(std::pair<Gene, Gene> g) {
	
	if(g.first == Elephant_Base::Gene::Y || g.second == Elephant_Base::Gene::Y)
		return Sex::Male;
	else
		return Sex::Female;
}

void Elephant_Base::Traits::generateGenes(Sex sex, bool hasTusks) {
	//if the elephant has tusks
	if(hasTusks) {
		
		switch(sex) {
			
			case Sex::Female:
				//can either be Xi/Xi or Xi/Xi_, since Xi is dominant
				genes = std::make_pair(Elephant_Base::Gene::Xi, Elephant_Base::randomGeneX());
				break;
			
			case Sex::Male:
				//has to be Xi/Y since Y doesn't hold the gene for tusks
				genes = std::make_pair(Elephant_Base::Gene::Xi, Elephant_Base::Gene::Y);
				break;
		}
		
	} else {
		
		switch(sex) {
			
			case Sex::Female:
				//has to be Xi_/Xi_ because Xi_ is recessive
				genes = std::make_pair(Elephant_Base::Gene::Xi_, Elephant_Base::Gene::Xi_);
				break;
			
			case Sex::Male:
				//has to be Xi_/Y since Y doesn't hold the gene for tusks
				genes = std::make_pair(Elephant_Base::Gene::Xi_, Elephant_Base::Gene::Y);
				break;
		}		
	}
}

void Elephant_Base::Traits::generateRandomGenes(Sex sex) {
	
	if(sex == Elephant_Base::Sex::Female){
		
		genes = std::make_pair(Elephant_Base::randomGeneX(), Elephant_Base::randomGeneX());
		
	} else {
		
		genes = std::make_pair(Elephant_Base::randomGeneX(), Elephant_Base::Gene::Y);
		
	}
}

/* destructor : */

Elephant_Base::~Elephant_Base() {
	
	mTraits.textures = nullptr;
}

/* public methods : */

void Elephant_Base::setEnclosure(sf::FloatRect limits) {
	
	mEnclosure = limits;
}

void Elephant_Base::kill() {
	
	mTraits.alive = false;
}

sf::Sprite Elephant_Base::getShape() const {
	
	return mShape;
}

sf::FloatRect Elephant_Base::getBoundaries() const {
	
	sf::FloatRect shapeBoundaries = mShape.getGlobalBounds();
	sf::FloatRect sprBoundaries(getPosition().x, getPosition().y, 
	shapeBoundaries.width, shapeBoundaries.height);
	
	return sprBoundaries;
}

sf::FloatRect Elephant_Base::getEnclosure() const {
	return mEnclosure;
}

Elephant_Base::Traits Elephant_Base::getTraits() const {
	
	return mTraits;
}

bool Elephant_Base::hasTusks() const {
	
	return mTraits.tusks;
}

bool Elephant_Base::isAlive() const {
	
	return mTraits.alive;
}

Elephant_Base::Gene Elephant_Base::randomGeneX() {
	
	return static_cast<Elephant_Base::Gene>(
	give_random(static_cast<int>(Elephant_Base::Gene::Xi), static_cast<int>(Elephant_Base::Gene::Xi_))
	);
}

/* protected methods : */

void Elephant_Base::toAge(sf::Time dt) {
	
	mTraits.age += dt.asSeconds() / YEAR_IN_SECONDS_VALUE.asSeconds();
	if(mTraits.age >= 70.f){
		kill();
	}
	
}

Elephant_Base::Gene Elephant_Base::generateGametes() const {
	
	/*A cell will give 4 gametes at the end of the meiosis. 
	 * But since we are studying only one pair of chromosomes,
	 * there will be only two different types of gametes with 
	 * either the first chromosome of the pair of the second one.
	 * This is why we make it a chance over 2.*/
	 
	 
	//if genes of the pair are the same, no need to calculate a random value
	if(mTraits.genes.first == mTraits.genes.second)
		return mTraits.genes.first;
		
	//random % 2 is either 1 or 0 with equal chances for both to happen
	int random = give_random(0, 999);
	if(random % 2 == 0){
		
		return mTraits.genes.first;
		
	} else {
		
		return mTraits.genes.second;
	}
}

void Elephant_Base::updateMovement(sf::Time dt) {
	
	constrain(mMovement, -20.f, 20.f);
	
	mMovement += random2D(-1.f, 1.f);
	
	move(round(mMovement.x) * dt.asSeconds(), round(mMovement.y) * dt.asSeconds());
	
	//make sure shape does not go off window
	
	if(getPosition().x < mEnclosure.left)
		move(mEnclosure.left - getPosition().x, 0);
		
	if(getPosition().x + mShape.getGlobalBounds().width > mEnclosure.width)
		move(mEnclosure.width - getPosition().x - mShape.getGlobalBounds().width, 0);
		
	if(getPosition().y < mEnclosure.top)
		move(0, mEnclosure.top - getPosition().y);
		
	if(getPosition().y + mShape.getGlobalBounds().height > mEnclosure.height)
		move(0, mEnclosure.height - getPosition().y - mShape.getGlobalBounds().height);
}


void Elephant_Base::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	
	states.transform *= getTransform();
	target.draw(mShape, states);
}