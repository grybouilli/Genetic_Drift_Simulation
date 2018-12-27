#include <Headers/TextureHolder.hpp>
#include <stdexcept>

void TextureHolder::load(std::string filename, Texture::ID id) {
	
	std::unique_ptr<sf::Texture> texturePtr( new sf::Texture() );
	
	if(!texturePtr->loadFromFile(filename)) {
		
		throw std::runtime_error("In TextureHolder::load() : Could not load file " + filename);
		return;
	}
	
	texturePtr->setSmooth(true);
	
	mTexturesMap.insert(std::make_pair(id, std::move(texturePtr)));
}

sf::Texture& TextureHolder::get(Texture::ID id) {
	
	auto found = mTexturesMap.find(id);
	return *found->second;
	
}

const sf::Texture& TextureHolder::get(Texture::ID id) const {
	
	auto found = mTexturesMap.find(id);
	return *found->second;
	
}

