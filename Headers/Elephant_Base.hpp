#ifndef GUARD_ELEPHANT_BASE_HPP
#define GUARD_ELEPHANT_BASE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Headers/TextureHolder.hpp"
#include <memory>

class Elephant_Base : public sf::Drawable, public sf::Transformable {
public:
	friend class Child_E;
	typedef float age_value;
	typedef Elephant_Base* Ptr;
	const static sf::Time YEAR_IN_SECONDS_VALUE; //represents the value of a year in a certain amount of seconds
	
	//enum to define if the Elephant is going to be male or female hence determining the sexual chromosomes
	enum Sex {
		
		Male,
		Female,
		None,
	};
	
	//it's actually the sexual chromosomes, but this app aims to study the gene that grows tusks on the elephants
	//Xi is dominant and is the gene that grows tusks
	enum Gene {
		
		Xi,
		Xi_,
		Y,
		Undefined,
	};
	
	struct Traits {
		
		Traits();
		Traits(TextureHolder& text, Sex s, bool hasTusks, age_value a = 0);
		Traits(TextureHolder& text, std::pair<Gene, Gene> g, age_value a = 0);
		
		Sex						sex;
		std::pair<Gene, Gene>   genes;
		bool 	  			 	tusks, alive;
		age_value 			 	age;
		
		TextureHolder* 			textures;
		
		static bool hasTusks(std::pair<Gene, Gene> g);
		static Sex	sexOf(std::pair<Gene, Gene> g);
		
	private:
		//generates random pair of Gene depending on the elephant's sex and tusks
		void 					generateGenes(Sex sex, bool hasTusks);
		//generate random pair of genes depending on sex
		void 					generateRandomGenes(Sex sex);
	};
	
public:
					Elephant_Base();
					Elephant_Base(TextureHolder& text, Elephant_Base::Sex sex, bool hasTusks, age_value a = 0);
	virtual		   ~Elephant_Base();
	
	//general methods
	virtual void 	update(sf::Time dt) = 0;
	
	void 		 	setEnclosure(sf::FloatRect limits); //sets a limit range in which the Elephant can move
	void		 	kill();
	
	bool		 	hasTusks() const; //returns true if mTraits.tusks = true, hence Elephant has tusks
	bool		 	isAlive() const;
	
	sf::Sprite		getShape() const;
	sf::FloatRect	getBoundaries() const;
	sf::FloatRect	getEnclosure() const;
	Traits	 	 	getTraits() const;//returns mTraits
	static Gene		randomGeneX();    //returns either Gene::Xi or Gene::Xi_ with equal chances for both
	
protected:
	//general functions
	void 		    toAge(sf::Time dt);
	Gene 	        generateGametes() const; //generates a random Gene amongst owned ones
	void		    updateMovement(sf::Time dt);
	
protected:
	sf::Sprite		mShape;

private:
	virtual void	draw(sf::RenderTarget& target, sf::RenderStates states) const;

	
private:
	//general members
	Traits			   mTraits;
	sf::Vector2f	   mMovement;
	sf::FloatRect  	   mEnclosure;	
};

#endif