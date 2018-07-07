#pragma once

#ifndef ASSETMANAGER_H_INCLUDED
#define ASSETMANAGER_H_INCLUDED

#include <map>
#include "../entity/Mesh.h"
#include "../core/Texture.h"
#include "ConsoleColour.h"
#include <vector>

class AssetManager
{

public:
	static AssetManager* Instance();
	virtual ~AssetManager();

	void LoadMesh(std::string name, std::string fileName);
	Mesh &GetMesh(std::string name);
	std::vector<std::string> loadedMeshes;

	void LoadTexturePropper(std::string name, std::string fileName);
	Texture &GetTexturePropper(std::string name);
	void BindTexturePropper(std::string name);
	unsigned int GetTextureId(std::string name);
	int GetLoadedTextureCount();
	void LoadTexture(std::string name, std::string filename);
	void ReloadTexture(std::string name, std::string filename);
	void BindTexture(std::string name);
	void BindTexture(unsigned int id);
	unsigned int GetTexture(std::string name);
	void DeleteTexture(std::string name);
	void DeleteTexture(unsigned int id);
	void DeleteAllTextures();

private:
	std::map<std::string, Mesh> m_meshes;
	std::map<std::string, Texture> m_textures;
	std::map<std::string, unsigned int> m_texIdMap;

protected:
	AssetManager();
	AssetManager(const AssetManager& ass);
	AssetManager& operator=(const AssetManager& ass);
	static AssetManager* m_instance;
};

#endif // !ASSETMANAGER_H_INCLUDED