#pragma once
#include "../util/GlmTypedefs.h"
#include <vector>
#include "../render/Renderer.h"
#include "../render/Vertex.h"

struct Mesh
{
public:
	/*std::vector	<Vector3> vertices;
	int VertCount = 0;
	void Recalculate() { VertCount = vertices.size(); };
	std::vector	<Vector2> uvs;
	std::vector	<Vector3> normals;
	void Render(unsigned int * vertBuffer, unsigned int * uvBuffer);*/


	//	NEW STUFF


public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indeces);
	void Draw(Shader shader);
private:
	unsigned int VAO, VBO, EBO;
	void Init();
};