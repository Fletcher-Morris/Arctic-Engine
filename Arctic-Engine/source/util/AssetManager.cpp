#include "AssetManager.h"
#include <iostream>
#include "../render/Renderer.h"
#include "../stb/stb_image.h"
#include <vector>
#include <chrono>

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
	auto startTime = std::chrono::high_resolution_clock::now();

	std::vector< glm::vec3 > input_positions;
	std::vector< glm::vec2 > input_uvs;
	std::vector< glm::vec3 > input_normals;
	std::vector<IndexTriplet> input_triplets;
	std::vector<Vertex> output_vertices;
	std::vector<unsigned int> output_indices;

	struct stat f;
	if (stat((fileName + ".mesh").c_str(), &f) == 0)
	{
		FILE * file = fopen((fileName + ".mesh").c_str(), "r");
		int res = 0;
		while (res != EOF) {
			char lineHeader[128];
			res = fscanf(file, "%s", lineHeader);
			if (strcmp(lineHeader, "r") == 0) {
				int rev;
				fscanf(file, "%d", &rev);
				if (rev != m_currentMeshRevision)
				{
					std::cout << m_currentMeshRevision << " != " << rev << std::endl;
					std::cout << red << "Mesh: " + fileName + " does not match current revision" << white << std::endl;
				}
			}
			else if (strcmp(lineHeader, "v") == 0) {
				Vertex newVertex;
				Vector3 position;
				Vector3 normal;
				Vector2 uv;
				fscanf(file, "%f %f %f %f %f %f %f %f", &position.x, &position.y, &position.z, &normal.x, &normal.y, &normal.z, &uv.x, &uv.y);
				newVertex.position = position;
				newVertex.normal = normal;
				newVertex.uv = uv;
				output_vertices.push_back(newVertex);
			}
			else if (strcmp(lineHeader, "i") == 0) {
				int ind;
				fscanf(file, "%d", &ind);
				output_indices.push_back(ind);
			}
		}

		Mesh newMesh(output_vertices, output_indices);
		newMesh.Init();
		this->m_meshes[name] = newMesh;
		if (std::find(loadedMeshes.begin(), loadedMeshes.end(), name) == loadedMeshes.end())
		{
			this->loadedMeshes.push_back(name);
		}
	}
	else
	{
		FILE * file = fopen(fileName.c_str(), "r");
		if (file == NULL) {
			std::cout << red << "Failed to load obj: " + fileName + "" << white << std::endl;
			return;
		}
		else {
			int res = 0;
			while (res != EOF) {
				char lineHeader[128];
				res = fscanf(file, "%s", lineHeader);
				Vertex temp_vertex;
				if (strcmp(lineHeader, "v") == 0) {
					Vector3 position;
					fscanf(file, "%f %f %f\n", &position.x, &position.y, &position.z);
					input_positions.push_back(position);
				}
				else if (strcmp(lineHeader, "vt") == 0) {
					Vector2 uv;
					fscanf(file, "%f %f\n", &uv.x, &uv.y);
					input_uvs.push_back(uv);
				}
				else if (strcmp(lineHeader, "vn") == 0) {
					Vector3 normal;
					fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
					input_normals.push_back(normal);
				}
				else if (strcmp(lineHeader, "f") == 0) {
					IndexTriplet trip[3];
					int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &trip[0].pos, &trip[0].uv, &trip[0].norm, &trip[1].pos, &trip[1].uv, &trip[1].norm, &trip[2].pos, &trip[2].uv, &trip[2].norm);
					if (matches != 9) {
						std::cout << red << "Error parsing obj file: " << fileName << white << std::endl;
						return;
					}
					for (int i = 0; i < 3; i++)
					{
						trip[i].pos--;
						trip[i].uv--;
						trip[i].norm--;
						input_triplets.push_back(trip[i]);
					}
				}
			}
			for (int i = 0; i < input_triplets.size(); i++)
			{
				Vector3 tempPos = input_positions[input_triplets[i].pos];
				Vector2 tempUv = input_uvs[input_triplets[i].uv];
				Vector3 tempNorm = input_normals[input_triplets[i].norm];
				int ind = FindExistingVertex(output_vertices, tempPos, tempUv, tempNorm);
				if (ind == -1)
				{
					Vertex newVert;
					newVert.position = tempPos;
					newVert.uv = tempUv;
					newVert.normal = tempNorm;

					output_vertices.push_back(newVert);
					ind = output_vertices.size() - 1;
				}
				output_indices.push_back(ind);
			}
			Mesh newMesh(output_vertices, output_indices);
			WriteMeshFile(newMesh, fileName);
			newMesh.Init();
			this->m_meshes[name] = newMesh;
			if (std::find(loadedMeshes.begin(), loadedMeshes.end(), name) == loadedMeshes.end())
			{
				this->loadedMeshes.push_back(name);
			}
		}
	}
	auto endTime = std::chrono::high_resolution_clock::now();
	double loadTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
	std::cout << "Loaded mesh: " + fileName + " in " << loadTime << "ms" << std::endl;
}

int AssetManager::FindExistingVertex(std::vector<Vertex> searchArea, Vector3 position, Vector2 uv, Vector3 normal)
{
	for (int i = 0; i < searchArea.size(); i++)
	{
		if (searchArea[i].position == position
			&& searchArea[i].normal == normal
			&& searchArea[i].uv == uv) return i;
	}
	return -1;
}

Mesh * AssetManager::GetMesh(std::string name)
{
	return &m_meshes.at(name);
}

void AssetManager::WriteMeshFile(Mesh mesh, std::string fileName)
{
	std::ofstream file(fileName + ".mesh");
	file << "# Mesh file generated by Arctic Engine" << std::endl;

	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	file << "# Created: " << (timePtr->tm_mday) << "/" << (timePtr->tm_mon) + 1 << "/" << (timePtr->tm_year) + 1900;
	file << " " << (timePtr->tm_hour) << ":" << (timePtr->tm_min) << ":" << (timePtr->tm_sec) << std::endl;

	std::string fileData;

	fileData.append("r ");
	fileData.append(std::to_string(m_currentMeshRevision));
	fileData.append("\n\n");

	int v = 0;
	while (v < mesh.vertices.size())
	{
		fileData.append("v ");
		fileData.append(std::to_string(mesh.vertices[v].position.x) + " ");
		fileData.append(std::to_string(mesh.vertices[v].position.y) + " ");
		fileData.append(std::to_string(mesh.vertices[v].position.z) + " ");
		fileData.append(std::to_string(mesh.vertices[v].normal.x) + " ");
		fileData.append(std::to_string(mesh.vertices[v].normal.y) + " ");
		fileData.append(std::to_string(mesh.vertices[v].normal.z) + " ");
		fileData.append(std::to_string(mesh.vertices[v].uv.x) + " ");
		fileData.append(std::to_string(mesh.vertices[v].uv.y));
		fileData.append("\n");
		v++;
	}
	int i = 0;
	while (i < mesh.indices.size())
	{
		fileData += "\ni ";
		fileData.append(std::to_string(mesh.indices[i]));
		i++;
	}
	file << "# " << v << " vertices" << std::endl;
	file << "# " << i << " indices" << std::endl;
	file << std::endl;
	file << fileData;
	file.close();
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
	auto  startTime = std::chrono::high_resolution_clock::now();

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

	auto endTime = std::chrono::high_resolution_clock::now();
	double loadTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
	std::cout << "Loaded texture: " << filename.c_str() << " in " << loadTime << "ms" << std::endl;
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

void AssetManager::AddShader(std::string _name)
{
	m_shaders[_name] = Shader();
}

void AssetManager::AddShader(std::string _name, std::string _path)
{
	m_shaders[_name] = Shader(_path);
}

Shader * AssetManager::GetShader(std::string _name)
{
	return &m_shaders.at(_name);
}

void AssetManager::RecompileShader(std::string _name, std::string _comboPath)
{
	m_shaders.at(_name).Compile(_comboPath);
}

void AssetManager::LoadMaterial(std::string _path)
{
	Material newMat = Material();

	FILE * file = fopen(_path.c_str(), "r");
	int res = 0;
	while (res != EOF) {
		char lineHeader[128];
		char line[128];
		res = fscanf(file, "%s", lineHeader);
		if (strcmp(lineHeader, "r") == 0) {
			int rev;
			fscanf(file, "%i", &rev);
			if (rev != m_currentMaterialRevision)
			{
				std::cout << m_currentMaterialRevision << " != " << rev << std::endl;
				std::cout << red << "Material: " + _path + " does not match current revision" << white << std::endl;
			}
		}
		else if (strcmp(lineHeader, "name") == 0) {
			std::string name;
			fscanf(file, "%s", &line);
			name = (std::string)line;
			if (name == "") { name = "test"; std::cout << red << "Material: " + _path + " couldn't load name" << white << std::endl; }
			newMat.SetName(name);
		}
		else if (strcmp(lineHeader, "shader") == 0) {
			std::string shader;
			fscanf(file, "%s", &line);
			shader = (std::string) line;
			if (shader == "") { shader = "standard"; std::cout << red << "Material: " + _path + " couldn't load shader" << white << std::endl;
			}
			newMat.SetShader(GetShader(shader));
		}
		else if (strcmp(lineHeader, "colour") == 0) {
			Vector3 colour;
			fscanf(file, "%d,%d,%d", &colour.x, &colour.y, &colour.z);
			newMat.SetColour(colour);
		}
		else if (strcmp(lineHeader, "textureid") == 0) {
			int texId;
			fscanf(file, "%d", &texId);
			newMat.SetTexture(texId);
		}
		else if (strcmp(lineHeader, "texture") == 0) {
			std::string texture;
			fscanf(file, "%s", &line);
			texture = (std::string) line;
			if (texture == "") { texture = "error"; std::cout << red << "Material: " + _path + " couldn't load texture" << white << std::endl; }
			newMat.SetTexture(GetTexture(texture));
		}
	}

	AddMaterial(newMat);
	std::cout << "Added Material : " << newMat.GetName() << std::endl;
}

void AssetManager::AddMaterial(std::string _name)
{
	AddMaterial(_name, Material());
}
void AssetManager::AddMaterial(std::string _name, Material _mat)
{
	m_materials[_name] = _mat;
}
void AssetManager::AddMaterial(Material _mat)
{
	AddMaterial(_mat.GetName(), _mat);
}
Material * AssetManager::GetMaterial(std::string _name)
{
	return &m_materials.at(_name);
}

AssetManager::AssetManager()
{
}

AssetManager::AssetManager(const AssetManager & ass)
{
}