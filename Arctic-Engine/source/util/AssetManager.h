#pragma once

#ifndef ASSETMANAGER_H_INCLUDED
#define ASSETMANAGER_H_INCLUDED

#include <map>
#include "NonMovable.h"
#include "../core/Obj.h"

class AssetManager : public NonCopyable, public NonMovable {

public:
	AssetManager() {}

	/*void LoadTexture(std::string name, std::string fileName);
	sf::Texture &GetTexture(std::string name);
	sf::Image PlaceholderImage();

	void  LoadImage(std::string name, std::string fileName);
	sf::Image &GetImage(std::string name);

	void LoadFont(std::string name, std::string fileName);
	sf::Font &GetFont(std::string name);*/

	bool LoadObj(std::string name, std::string fileName);
	Obj &GetObj(std::string name);

private:
	/*std::map<std::string, sf::Texture> _textures;
	std::map<std::string, sf::Image> _images;
	std::map<std::string, sf::Font> _fonts;*/
	std::map<std::string, Obj> _objs;
};

#endif // !ASSETMANAGER_H_INCLUDED