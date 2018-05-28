#include "AssetManager.h"
#include <iostream>
#include "../render/Renderer.h"
#include "../stb/stb_image.h"

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

void AssetManager::LoadObj(std::string name, std::string fileName)
{

	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	FILE * file = fopen(fileName.c_str(),"r");
	if (file == NULL) {
		std::cout << red << "Failed to load obj: " + fileName + "" << std::endl;
		return;
	}
	else {
		int res = 0;
		while (res != EOF) {
			char lineHeader[128];
			res = fscanf(file, "%s", lineHeader);

			if (strcmp(lineHeader, "v") == 0) {
				glm::vec3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				temp_vertices.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0) {
				glm::vec2 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				temp_uvs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0) {
				glm::vec3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				temp_normals.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0) {
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9) {
					std::cout << red << "Error parsing obj file: " << fileName << std::endl;
					return;
				}
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}

		Obj obj;

		for (unsigned int i = 0; i < vertexIndices.size(); i++) {
			unsigned int vertexIndex = vertexIndices[i];
			glm::vec3 vertex = temp_vertices[vertexIndex - 1];
			obj.vertices.push_back(vertex);
		}
		for (unsigned int i = 0; i < uvIndices.size(); i++) {
			unsigned int uvIndex = uvIndices[i];
			glm::vec2 uv = temp_uvs[uvIndex - 1];
			obj.uvs.push_back(uv);
		}
		for (unsigned int i = 0; i < normalIndices.size(); i++) {
			unsigned int normalIndex = normalIndices[i];
			glm::vec3 normal = temp_normals[normalIndex - 1];
			obj.normals.push_back(normal);
		}

		this->m_objs[name] = obj;
		std::cout << "Loaded obj: " + fileName + "" << std::endl;
		return;
	}
}

Obj& AssetManager::GetObj(std::string name)
{
	return this->m_objs.at(name);
}

void AssetManager::LoadTexturePropper(std::string name, std::string fileName)
{
	Texture t = Texture(fileName);

	this->m_textures[name] = t;
	std::cout << "Loaded texture: " + fileName + " , GLID = " << t.m_textureId << std::endl;
	return;
}

void AssetManager::AddTexture(std::string name, Texture tex)
{
	AddTexture(tex, name);
}
void AssetManager::AddTexture(Texture tex, std::string name)
{
	this->m_textures[name] = tex;
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
	std::cout << "Generated texture to " << m_textureId << std::endl;

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	if (m_data) {
		GLCall(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data));
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
		stbi_image_free(m_data);
	}
	else
	{
		std::cout << "Failed to parse texture '" << filename << "'" << std::endl;
	}
}

void AssetManager::BindTexture(std::string name)
{
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_texIdMap.at(name)));
}

unsigned int AssetManager::GetTexture(std::string name)
{
	return m_texIdMap.at(name);
}



AssetManager::AssetManager()
{
}

AssetManager::AssetManager(const AssetManager & ass)
{
}