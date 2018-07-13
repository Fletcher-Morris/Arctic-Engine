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


	//	Position
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0));
	//	Normal
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal)));
	//	Tex Coords
	GLCall(glEnableVertexAttribArray(2));
	GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords)));

	GLCall(glBindVertexArray(0));
}

void Mesh::Draw(Shader shader)
{


	//	Draw Mesh
	GLCall(glBindVertexArray(VAO));
	GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
	GLCall(glBindVertexArray(0));
}