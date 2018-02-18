#pragma once

#ifndef ASSETMANAGER_H_INCLUDED
#define ASSETMANAGER_H_INCLUDED

#include <map>
#include <SFML/Graphics.hpp>
#include "NonMovable.h"

class AssetManager : public NonCopyable, public NonMovable {

public:
	AssetManager() {}

	void LoadTexture(std::string name, std::string fileName);
	sf::Texture &GetTexture(std::string name);
	sf::Texture PlaceholderTexture();

	void LoadFont(std::string name, std::string fileName);
	sf::Font &GetFont(std::string name);

private:
	std::map<std::string, sf::Texture> _textures;
	std::map<std::string, sf::Font> _fonts;
};

#endif // !ASSETMANAGER_H_INCLUDED