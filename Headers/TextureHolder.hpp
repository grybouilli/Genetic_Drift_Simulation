#ifndef GUARD_TEXTUREHOLDER_HPP
#define GUARD_TEXTUREHOLDER_HPP

#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <map>
#include <memory>

namespace Texture {
	
	enum ID {
		
		TuskedFemale,
		TuskedMale,
		UntuskedFemale,
		UntuskedMale,
		Background,
	};
}

class TextureHolder : private sf::NonCopyable {
public:
	void												 load(std::string filename, Texture::ID id);
	
	sf::Texture&										 get(Texture::ID id);
	const sf::Texture& 									 get(Texture::ID id) const;
	
private:
	std::map<Texture::ID, std::unique_ptr<sf::Texture> > mTexturesMap;
};

#endif