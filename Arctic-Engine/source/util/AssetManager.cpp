#include "AssetManager.h"
#include <iostream>
#include "../render/Renderer.h"
#include "../stb/stb_image.h"
#include <vector>

AssetManager * AssetManager::m_instance(0);

AssetManager * AssetManager::Instance()
{
	if (!m_instance) m_instance = new AssetManager();
	return m_instance;
}

AssetManager::~AssetManager()
{
	m_instance = 0;
}

void AssetManager::LoadMesh(std::string name, std::string fileName)
{

	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices, allIndices;
	std::vector< glm::vec3 > temp_positions;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	int posCount = 0;
	int normCount = 0;
	int uvCount = 0;

	std::vector<Vertex> temp_vertices;

	FILE * file = fopen(fileName.c_str(),"r");
	if (file == NULL) {
		std::cout << red << "Failed to load mesh: " + fileName + "" << std::endl;
		return;
	}
	else {
		int res = 0;
		while (res != EOF) {
			char lineHeader[128];
			res = fscanf(file, "%s", lineHeader);

			if (strcmp(lineHeader, "v") == 0) {
				glm::vec3 position;
				fscanf(file, "%f %f %f\n", &position.x, &position.y, &position.z);
				temp_positions.push_back(position);
				posCount++;
			}
			else if (strcmp(lineHeader, "vt") == 0) {
				glm::vec2 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				temp_uvs.push_back(uv);
				uvCount++;
			}
			else if (strcmp(lineHeader, "vn") == 0) {
				glm::vec3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				temp_normals.push_back(normal);
				normCount++;
			}
			else if (strcmp(lineHeader, "f") == 0) {
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9) {
					std::cout << red << "Error parsing obj file: " << fileName << std::endl;
					return;
				}

				int method = 1;

				if (method == 0)
				{
					//	v,u,n,v,u,n,v,u,n
					allIndices.push_back(vertexIndex[0] - 1);
					allIndices.push_back(uvIndex[0] - 1);
					allIndices.push_back(normalIndex[0] - 1);
					allIndices.push_back(vertexIndex[1] - 1);
					allIndices.push_back(uvIndex[1] - 1);
					allIndices.push_back(normalIndex[1] - 1);
					allIndices.push_back(vertexIndex[2] - 1);
					allIndices.push_back(uvIndex[2] - 1);
					allIndices.push_back(normalIndex[2] - 1);
				}
				else if (method == 1)
				{
					//	v,v,v,u,u,u,n,n,n
					allIndices.push_back(vertexIndex[0] - 1);
					allIndices.push_back(vertexIndex[1] - 1);
					allIndices.push_back(vertexIndex[2] - 1);
					allIndices.push_back(uvIndex[0] - 1);
					allIndices.push_back(uvIndex[1] - 1);
					allIndices.push_back(uvIndex[2] - 1);
					allIndices.push_back(normalIndex[0] - 1);
					allIndices.push_back(normalIndex[1] - 1);
					allIndices.push_back(normalIndex[2] - 1);
				}
			}
		}

		int maxVertSize = allIndices.size() / 9;

		for (int i = 0; i < maxVertSize; i++)
		{
			Vertex tempVertex;
			if (posCount > i){tempVertex.position = temp_positions[i];}
			else { tempVertex.position = Vector3{ 0,0,0 }; }
			if (uvCount > i){tempVertex.uv = temp_uvs[i];}
			else { tempVertex.uv = Vector2{ 0,0 }; }
			if (normCount > i){tempVertex.normal = temp_normals[i];}
			else { tempVertex.normal = Vector3{ 0,0,0 }; }

			temp_vertices.push_back(tempVertex);
		}


		Mesh newMesh(temp_vertices, allIndices);

		newMesh.Init();

		this->m_meshes[name] = newMesh;
		
		if(std::find(loadedMeshes.begin(), loadedMeshes.end(), name) == loadedMeshes.end())
		{
			this->loadedMeshes.push_back(name);
		}

		std::cout << "Loaded mesh: " + fileName + "" << std::endl;

		return;
	}
}

Mesh * AssetManager::GetMesh(std::string name)
{
	return &m_meshes.at(name);
}

void AssetManager::LoadTexturePropper(std::string name, std::string fileName)
{
	Texture t = Texture(fileName);

	this->m_textures[name] = t;
	std::cout << "Loaded texture: " + fileName + " , GLID = " << t.m_textureId << std::endl;
	return;
}
Texture& AssetManager::GetTexturePropper(std::string name)
{
	return this->m_textures.at(name);
}
void AssetManager::BindTexturePropper(std::string name)
{
	m_textures.at(name).Bind();
}


unsigned int AssetManager::GetTextureId(std::string name)
{
	return m_textures.at(name).m_textureId;
}
int AssetManager::GetLoadedTextureCount()
{
	return m_texIdMap.size();
}
void AssetManager::LoadTexture(std::string name, std::string filename)
{
	unsigned char * m_data;
	int m_width, m_height, m_bits;
	unsigned int m_textureId;


	m_data = stbi_load(filename.c_str(), &m_width, &m_height, &m_bits, 4);
	
	GLCall(glGenTextures(1, &m_textureId));
	m_texIdMap[name] = m_textureId;
	GLCall(glBindTexture(GL_TEXTURE_2D, m_textureId));

	if (m_data) {
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data));
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
		stbi_image_free(m_data);
	}
	else
	{
		std::cout << "Failed to load texture '" << filename << "'" << std::endl;		
		int size = 8;
		m_width = size;
		m_height = size;
		m_bits = 3;
		std::vector<unsigned char>errorTex(m_height * m_width * 3);
		bool evenRow = false;
		bool evenPixel = false;
		for (int i = 0; i < m_width * m_height * m_bits; i += m_bits)
		{
			if (i % m_width == 0) { evenRow = !evenRow; }
			if (evenRow)
			{
				if (i % 2 == 0) {
					errorTex[i] = 255;
					errorTex[i + 1] = 0;
					errorTex[i + 2] = 255;
				}
			}
			else {
				if (i % 2 != 0) {
					errorTex[i] = 255;
					errorTex[i + 1] = 0;
					errorTex[i + 2] = 255;
				}
			}
		}

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, &errorTex[0]));
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
		stbi_image_free(m_data);
	}
}
void AssetManager::ReloadTexture(std::string name, std::string filename)
{
	unsigned char * m_data;
	int m_width, m_height, m_bits;
	unsigned int m_textureId;


	m_data = stbi_load(filename.c_str(), &m_width, &m_height, &m_bits, 4);

	m_textureId = GetTextureId(name);
	GLCall(glBindTexture(GL_TEXTURE_2D, m_textureId));

	if (m_data) {
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data));
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
		stbi_image_free(m_data);
	}
	else
	{
		std::cout << "Failed to load texture '" << filename << "'" << std::endl;
		int size = 8;
		m_width = size;
		m_height = size;
		m_bits = 3;
		std::vector<unsigned char>errorTex(m_height * m_width * 3);
		bool evenRow = false;
		bool evenPixel = false;
		for (int i = 0; i < m_width * m_height * m_bits; i += m_bits)
		{
			if (i % m_width == 0) { evenRow = !evenRow; }
			if (evenRow)
			{
				if (i % 2 == 0) {
					errorTex[i] = 255;
					errorTex[i + 1] = 0;
					errorTex[i + 2] = 255;
				}
			}
			else {
				if (i % 2 != 0) {
					errorTex[i] = 255;
					errorTex[i + 1] = 0;
					errorTex[i + 2] = 255;
				}
			}
		}

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, &errorTex[0]));
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
		stbi_image_free(m_data);
	}
}
void AssetManager::BindTexture(std::string name)
{
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_texIdMap.at(name)));
}
void AssetManager::BindTexture(unsigned int id)
{
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, id));
}
unsigned int AssetManager::GetTexture(std::string name)
{
	return m_texIdMap.at(name);
}

void AssetManager::DeleteTexture(std::string name)
{
}

void AssetManager::DeleteTexture(unsigned int id)
{
}

void AssetManager::DeleteAllTextures()
{
}


AssetManager::AssetManager()
{
}

AssetManager::AssetManager(const AssetManager & ass)
{
}