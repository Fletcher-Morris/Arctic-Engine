#include "Mesh.h"

void Mesh::Render(unsigned int * vertBuffer, unsigned int * uvBuffer)
{
	////	VERTEX BUFFER
	//glGenBuffers(1, vertBuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, *vertBuffer);
	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector3), &vertices[0], GL_STATIC_DRAW);

	////	UV BUFFER
	//glGenBuffers(1, uvBuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, *uvBuffer);
	//glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(Vector2), &uvs[0], GL_STATIC_DRAW);

	//glDrawArrays(GL_TRIANGLES, 0, VertCount);
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indeces)
{
	this->vertices = vertices;
	this->indices = indeces;
	Init();
}

void Mesh::Init()
{
	GLCall(glGenVertexArrays(1, &VAO));
	GLCall(glGenBuffers(1, &VBO));
	GLCall(glGenBuffers(1, &EBO));

	GLCall(glBindVertexArray(VAO));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));

	GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW));

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW));
}