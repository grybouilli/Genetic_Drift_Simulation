#include "Headers/Application.hpp"
#include <SFML/Window/VideoMode.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "Headers/randomVector.hpp"
#include <iostream>
#include <memory>

const sf::Time Application::TimePerFrame = sf::seconds(1.f/30.f);

Application::Application()
: mWindow(sf::VideoMode(1920,1067), "Where are the tusks?",  sf::Style::Close | sf::Style::Titlebar)
, mWorld(sf::FloatRect(0, 0, mWindow.getSize().x, mWindow.getSize().y), mTextures){
	loadTextures();
	mWorld.generateWorld(4, 2);
}

void Application::run() {
	
	sf::Clock clock;
	sf::Time elapsed = sf::Time::Zero;
	
	while(mWindow.isOpen()) {
		
		elapsed = clock.restart();
		do {
			
			processEvents();
			update(TimePerFrame);
			
			elapsed -= TimePerFrame;
			
		} while(elapsed > TimePerFrame);
		
		render();
	}
}

void Application::update(sf::Time dt) {

	mWorld.update(dt);
}

void Application::processEvents() {
	
	sf::Event event;
	while(mWindow.pollEvent(event)) { 
		
		if(event.type == sf::Event::Closed)
			mWindow.close();
		
	}
}

void Application::render() {
	
	mWindow.clear();
	mWindow.draw(mWorld);
	mWindow.display();
}

void Application::loadTextures() {
	
	mTextures.load("medias/FemaleTusked.png", Texture::TuskedFemale);
	mTextures.load("medias/FemaleUntusked.png", Texture::UntuskedFemale);
	mTextures.load("medias/MaleTusked.png", Texture::TuskedMale);
	mTextures.load("medias/MaleUntusked.png", Texture::UntuskedMale);
	mTextures.load("medias/Background.png", Texture::Background);
}