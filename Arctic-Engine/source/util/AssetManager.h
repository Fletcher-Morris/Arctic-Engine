#pragma once

#ifndef ASSETMANAGER_H_INCLUDED
#define ASSETMANAGER_H_INCLUDED

#include <map>
#include "../core/Obj.h"
#include "../core/Texture.h"

class AssetManager
{

public:
	static AssetManager* Instance();
	virtual ~AssetManager();

	void LoadObj(std::string name, std::string fileName);
	Obj &GetObj(std::string name);

	void LoadTexture(std::string name, std::string fileName);
	void AddTexture(std::string name, Texture tex);
	void AddTexture(Texture tex, std::string name);
	Texture &GetTexture(std::string name);
	void BindTexture(std::string name);
	unsigned int GetTextureId(std::string name);
	int GetLoadedTextureCount();

private:
	std::map<std::string, Obj> m_objs;
	std::map<std::string, Texture> m_textures;

protected:
	AssetManager();
	AssetManager(const AssetManager& ass);
	AssetManager& operator=(const AssetManager& ass);
	static AssetManager* m_instance;
};

#endif // !ASSETMANAGER_H_INCLUDED