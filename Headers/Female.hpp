#ifndef GUARD_FEMALE_HPP
#define GUARD_FEMALE_HPP

#include "Headers/Elephant_Base.hpp"
#include <SFML/System/Time.hpp>
#include "Headers/TextureHolder.hpp"
#include "Headers/Child.hpp"

class Female_E : public Elephant_Base {
	friend class Male_E;
public:
					Female_E();
					Female_E(TextureHolder& text, bool hasTusks, age_value a = 0);
					
	void			update(sf::Time dt);
	
	//female methods
	bool 				canGetPregnant() const;
	bool				hasChildGrown() const;
	Elephant_Base::Ptr	detachChild();
	bool 				isPregnant() const;
	
private:
	//female functions
	void			makePregnant(const Elephant_Base::Gene& maleGamete);
	void			giveBirth(); //called in update; will create a child
	
private:
	virtual void	draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
private:
	//female members
	Child_E			   mChild;
	bool			   mIsPregnant;
	age_value		   mGestationTime;	
	
};

#endif