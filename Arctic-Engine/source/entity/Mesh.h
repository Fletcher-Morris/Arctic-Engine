#pragma once
#include "../util/GlmTypedefs.h"
#include <vector>
#include "../render/Renderer.h"
#include "../render/Vertex.h"

struct Mesh
{
public:
	Mesh();
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indeces);
	void Render();
	void Init();
private:
	unsigned int VAO, VBO, EBO;
};