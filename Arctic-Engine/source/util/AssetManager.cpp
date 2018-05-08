#include "AssetManager.h"
#include <iostream>
#include "NonCopyable.h"

//void AssetManager::LoadTexture(std::string name, std::string fileName)
//{
//	sf::Texture tex;
//
//	if (tex.loadFromFile(fileName)) {
//		this->_textures[name] = tex;
//
//		std::cout << "Loaded texture: " + fileName + "" << std::endl;
//	}
//	else {
//		std::cout << "Failed to load texture: " + fileName + "" << std::endl;
//		sf::Texture tex;
//		tex.loadFromImage(PlaceholderImage());
//		this->_textures[name] = tex;
//	}
//}
//sf::Texture &AssetManager::GetTexture(std::string name) {
//	return this->_textures.at(name);
//}
//sf::Image AssetManager::PlaceholderImage()
//{
//	//  Generate a pink and black place-holder texture
//	sf::Image missingImage;
//	missingImage.create(128, 128, sf::Color::Black);
//
//	int cY = 0;
//	int cX = 0;
//
//	for (int y = 0; y < 128; y++) {
//		for (int x = 0; x < 128; x++) {
//			if ((cX + cY) / 2 < 8) {
//				missingImage.setPixel(x, y, sf::Color(255, 20, 147, 255));
//			}
//			else {
//				missingImage.setPixel(x, y, sf::Color(0, 0, 0, 255));
//			}
//			cX++;
//			if (cY >= 16)
//				cY = 0;
//			if (cX >= 16)
//				cX = 0;
//		}
//		cY++;
//	}
//
//	return missingImage;
//}
//
//void AssetManager::LoadImage(std::string name, std::string fileName)
//{
//	sf::Image image;
//
//	if (image.loadFromFile(fileName)) {
//		this->_images[name] = image;
//
//		std::cout << "Loaded image: " + fileName + "" << std::endl;
//	}
//	else {
//		std::cout << "Failed to load image: " + fileName + "" << std::endl;
//		this->_images[name] = PlaceholderImage();
//	}
//}
//
//sf::Image & AssetManager::GetImage(std::string name)
//{
//	return this->_images.at(name);
//}
//
//void AssetManager::LoadFont(std::string name, std::string fileName)
//{
//	sf::Font font;
//
//	if (font.loadFromFile(fileName)) {
//		this->_fonts[name] = font;
//
//		std::cout << "Loaded font: " + fileName + "" << std::endl;
//	}
//	else {
//		std::cout << "Failed to load font: " + fileName + "" << std::endl;
//	}
//}
//sf::Font &AssetManager::GetFont(std::string name) {
//	return this->_fonts.at(name);
//}

bool AssetManager::LoadObj(std::string name, std::string fileName)
{

	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	FILE * file = fopen(fileName.c_str(),"r");
	if (file == NULL) {
		//std::cout << "Failed to load obj: " + fileName + "" << std::endl;
		return false;
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
					//std::cout << "Error parsing obj file: " << fileName << std::endl;
					return false;
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

		this->_objs[name] = obj;
		//std::cout << "Loaded obj: " + fileName + "" << std::endl;
		return true;
	}
}

Obj & AssetManager::GetObj(std::string name)
{
	return this->_objs.at(name);
}
