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
	Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indeces);
	void Render(int _method);
	void Init();

private:
	unsigned int VAO, VBO, EBO;

	int m_vertexCount = 0;
	int m_indexCount = 0;
	unsigned long long m_sizeOfVertex;
};