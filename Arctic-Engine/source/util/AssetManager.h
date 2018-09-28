#pragma once

#ifndef ASSETMANAGER_H_INCLUDED
#define ASSETMANAGER_H_INCLUDED

#include <map>
#include "../entity/Mesh.h"
#include "../core/Texture.h"
#include "../render/Material.h"
#include "ConsoleColour.h"
#include <vector>

class AssetManager
{

public:
	static AssetManager* Instance();
	virtual ~AssetManager();

	void LoadMesh(std::string _name, std::string _fileName);
	Mesh * GetMesh(std::string _name);
	std::vector<std::string> loadedMeshes;
	void WriteMeshFile(Mesh mesh, std::string _fileName);

	void LoadTexturePropper(std::string _name, std::string _fileName);
	Texture &GetTexturePropper(std::string _name);
	void BindTexturePropper(std::string _name);
	unsigned int GetTextureId(std::string _name);
	int GetLoadedTextureCount();
	void LoadTexture(std::string _name, std::string _fileName);
	void ReloadTexture(std::string _name, std::string _fileName);
	void BindTexture(std::string _name);
	void BindTexture(unsigned int _id);
	unsigned int GetTexture(std::string _name);
	void DeleteTexture(std::string _name);
	void DeleteTexture(unsigned int _id);
	void DeleteAllTextures();

	void AddShader(std::string _name);
	void AddShader(std::string _name, std::string _path);
	Shader * GetShader(std::string _name);
	void RecompileShader(std::string _name, std::string _comboPath);

	void AddMaterial(std::string _name);
	Material * GetMaterial(std::string _name);

private:

	//	Maps for the various asset types
	std::map<std::string, Mesh> m_meshes;
	std::map<std::string, Texture> m_textures;
	std::map<std::string, unsigned int> m_texIdMap;
	std::map<std::string, Shader> m_shaders;
	std::map<std::string, Material> m_materials;

	int m_currentMeshRevision = 1;
	int FindExistingVertex(std::vector<Vertex> _searchArea, Vector3 _position, Vector2 _uv, Vector3 _normal);

protected:
	AssetManager();
	AssetManager(const AssetManager& _ass);
	AssetManager& operator=(const AssetManager& _ass);
	static AssetManager* m_instance;
};

#endif // !ASSETMANAGER_H_INCLUDED