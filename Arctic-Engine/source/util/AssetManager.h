#pragma once

#ifndef ASSETMANAGER_H_INCLUDED
#define ASSETMANAGER_H_INCLUDED

#include <map>
#include "NonMovable.h"
#include "../core/Obj.h"
#include "../core/Texture.h"

class AssetManager : public NonCopyable, public NonMovable {

public:
	AssetManager() {}

	void LoadObj(std::string name, std::string fileName);
	Obj &GetObj(std::string name);

	void LoadTexture(std::string name, std::string fileName);
	void AddTexture(std::string name, Texture tex);
	void AddTexture(Texture tex, std::string name);
	Texture &GetTexture(std::string name);

	void SomeFunction();

private:
	std::map<std::string, Obj> m_objs;
	std::map<std::string, Texture> m_textures;
};

#endif // !ASSETMANAGER_H_INCLUDED