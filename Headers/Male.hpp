#ifndef GUARD_MALE_HPP
#define GUARD_MALE_HPP

#include "Elephant_Base.hpp"
#include <memory>
#include "Female.hpp"

class Male_E : public Elephant_Base {
public:
					Male_E();
					Male_E(TextureHolder& text, bool hasTusks, age_value a = 0);
					
	void		 	update(sf::Time dt);
	
	bool			isMeeting(const Female_E& f) const;
	void			tryToMate(Female_E& f);
	
private:
	virtual void	draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif