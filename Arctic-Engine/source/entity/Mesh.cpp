#include "Mesh.h"


Mesh::Mesh()
{
}

Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices)
{
	this->vertices = _vertices;
	this->indices = _indices;
	Init();
}

void Mesh::Init()
{
	m_vertexCount = vertices.size();
	m_indexCount = indices.size();
	m_sizeOfVertex = sizeof(Vertex);

	GLCall(glGenVertexArrays(1, &VAO));
	GLCall(glGenBuffers(1, &VBO));
	GLCall(glGenBuffers(1, &EBO));

	GLCall(glBindVertexArray(VAO));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));

	GLCall(glBufferData(GL_ARRAY_BUFFER, m_vertexCount * m_sizeOfVertex, &vertices[0], GL_STATIC_DRAW));

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW));


	//	Position
	
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, m_sizeOfVertex, (void*)0));
	GLCall(glEnableVertexAttribArray(0));
	//	Normals

	GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, m_sizeOfVertex, (void*)offsetof(Vertex, normal)));
	GLCall(glEnableVertexAttribArray(1));
	//	Tex Coords

	GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, m_sizeOfVertex, (void*)offsetof(Vertex, uv)));
	GLCall(glEnableVertexAttribArray(2));

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
}

void Mesh::Render(int _method)
{
	//	Draw Mesh
	GLCall(glBindVertexArray(VAO));

	if (_method == 0)
	{
		GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
	}
	else if (_method == 1)
	{
		GLCall(glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0));
	}
	else if (_method == 2)
	{
		GLCall(glDrawElements(GL_POINTS, indices.size(), GL_UNSIGNED_INT, 0));
	}
}