#include "AssetManager.h"
#include <iostream>
#include "NonCopyable.h"

void AssetManager::LoadTexture(std::string name, std::string fileName)
{
	sf::Texture tex;

	if (tex.loadFromFile(fileName)) {
		this->_textures[name] = tex;

		std::cout << "Loaded " + fileName + "" << std::endl;
	}
	else {
		this->_textures[name] = PlaceholderTexture();
	}
}
sf::Texture &AssetManager::GetTexture(std::string name) {
	return this->_textures.at(name);
}
sf::Texture AssetManager::PlaceholderTexture()
{
	//  Generate a pink and black place-holder texture
	sf::Image missingImage;
	missingImage.create(128, 128, sf::Color::Black);

	int cY = 0;
	int cX = 0;

	for (int y = 0; y < 128; y++) {
		for (int x = 0; x < 128; x++) {
			if ((cX + cY) / 2 < 8) {
				missingImage.setPixel(x, y, sf::Color(255, 20, 147, 255));
			}
			else {
				missingImage.setPixel(x, y, sf::Color(0, 0, 0, 255));
			}
			cX++;
			if (cY >= 16)
				cY = 0;
			if (cX >= 16)
				cX = 0;
		}
		cY++;
	}

	sf::Texture PlaceholderTexture;
	PlaceholderTexture.loadFromImage(missingImage);

	return PlaceholderTexture;
}



void AssetManager::LoadFont(std::string name, std::string fileName)
{
	sf::Font font;

	if (font.loadFromFile(fileName)) {
		this->_fonts[name] = font;

		std::cout << "Loaded " + fileName + "" << std::endl;
	}
	else {

	}
}
sf::Font &AssetManager::GetFont(std::string name) {
	return this->_fonts.at(name);
}