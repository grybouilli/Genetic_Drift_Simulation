#ifndef GUARD_APPLICATION_HPP
#define GUARD_APPLICATION_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include "World.hpp"
#include "TextureHolder.hpp"

class Application {
public:
	Application();
	
	void run();
	
private:
	void update(sf::Time dt);
	void processEvents();
	void render();
	
	void loadTextures();
	
private:
	static const sf::Time TimePerFrame;
	
	TextureHolder		  mTextures;
	sf::RenderWindow	  mWindow;
	//Male_E			  mElephant;
	World				  mWorld;
};

#endif