#include "Mesh.h"


Mesh::Mesh()
{
}

Mesh::Mesh(std::vector<Vertex> newVertices, std::vector<unsigned int> newIndices)
{
	this->vertices = newVertices;
	this->indices = newIndices;

	/*for (int i = 0; i < vertices.size(); i++)
	{
		float x = vertices[i].position.x;
		float y = vertices[i].position.y;
		float z = vertices[i].position.z;
		std::cout << "Positions: " << x << "," << y << "," << z << std::endl;

		x = vertices[i].normal.x;
		y = vertices[i].normal.y;
		z = vertices[i].normal.z;
		std::cout << "Normals: " << x << "," << y << "," << z << std::endl;

		x = vertices[i].uv.x;
		y = vertices[i].uv.y;
		std::cout << "UV: " << x << "," << y << std::endl << std::endl;
	}

	for (int i = 0; i < indices.size(); i++)
	{
		std::cout << indeces[i] << ",";
	}
	std::cout << std::endl;*/


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
	
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0));
	GLCall(glEnableVertexAttribArray(0));
	//	Normals

	GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal)));
	GLCall(glEnableVertexAttribArray(1));
	//	Tex Coords

	GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv)));
	GLCall(glEnableVertexAttribArray(2));

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
}

void Mesh::Render()
{
	//	Draw Mesh
	GLCall(glBindVertexArray(VAO));
	GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
}