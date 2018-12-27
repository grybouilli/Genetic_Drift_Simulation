#ifndef GUARD_CHILD_HPP
#define GUARD_CHILD_HPP

#include "Headers/Elephant_Base.hpp"
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Child_E : public Elephant_Base {
public:
						Child_E();
						Child_E(TextureHolder& text, std::pair<Elephant_Base::Gene, Elephant_Base::Gene> g, age_value a = 0);
					
	void				update(sf::Time dt);
	
	Elephant_Base::Ptr	getData() const;
	
	operator bool() const {
		if(mPtr)
			return true;
		else
			return false;
	}
	
private:
	virtual void 		draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
private:
	Elephant_Base::Ptr	mPtr;
	
};

//class Child_E : public sf::Drawable, public sf::Transformable {
//public:
//							 ~Child_E();
//							 Child_E();
//							 Child_E(TextureHolder& text, std::pair<Elephant_Base::Gene, Elephant_Base::Gene> g, 
//							 Elephant_Base::age_value a = 0);
//					
//	void					 update(sf::Time dt);
//	
//	Elephant_Base::Ptr		 getData() const;
//	Elephant_Base::age_value getAge() const;
//	
//	operator bool() const {
//		if(mPtr)
//			return true;
//		else
//			return false;
//	}
//	
//private:
//	virtual void 			 draw(sf::RenderTarget& target, sf::RenderStates states) const;
//	
//private:
//	Elephant_Base::Ptr		 mPtr;
//	sf::Sprite				 mShape;
//	
//};


#endif