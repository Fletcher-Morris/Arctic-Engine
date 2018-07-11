#include "Mesh.h"

void Mesh::Render(unsigned int * vertBuffer, unsigned int * uvBuffer)
{
	//	VERTEX BUFFER
	glGenBuffers(1, vertBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, *vertBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector3), &vertices[0], GL_STATIC_DRAW);

	//	UV BUFFER
	glGenBuffers(1, uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, *uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(Vector2), &uvs[0], GL_STATIC_DRAW);

	glDrawArrays(GL_TRIANGLES, 0, VertCount);
}
