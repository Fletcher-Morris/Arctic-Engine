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
		std::cout << "Failed to load " + fileName + "" << std::endl;
		sf::Texture tex;
		tex.loadFromImage(PlaceholderImage());
		this->_textures[name] = tex;
	}
}
sf::Texture &AssetManager::GetTexture(std::string name) {
	return this->_textures.at(name);
}
sf::Image AssetManager::PlaceholderImage()
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

	return missingImage;
}

void AssetManager::LoadImage(std::string name, std::string fileName)
{
	sf::Image image;

	if (image.loadFromFile(fileName)) {
		this->_images[name] = image;

		std::cout << "Loaded " + fileName + "" << std::endl;
	}
	else {
		std::cout << "Failed to load " + fileName + "" << std::endl;
		this->_images[name] = PlaceholderImage();
	}
}

sf::Image & AssetManager::GetImage(std::string name)
{
	return this->_images.at(name);
}

void AssetManager::LoadFont(std::string name, std::string fileName)
{
	sf::Font font;

	if (font.loadFromFile(fileName)) {
		this->_fonts[name] = font;

		std::cout << "Loaded " + fileName + "" << std::endl;
	}
	else {
		std::cout << "Failed to load " + fileName + "" << std::endl;
	}
}
sf::Font &AssetManager::GetFont(std::string name) {
	return this->_fonts.at(name);
}