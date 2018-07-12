#include "Entity.h"

Entity::Entity()
{
	name = "New Entity";
}

Entity::Entity(std::string _name)
{
	name = _name;
	SetMesh(_name);
}

Entity::Entity(std::string _name, std::string _meshName)
{
	name = _name;
	SetMesh(_meshName);
}

void Entity::SetMesh(Mesh * newMesh)
{
	mesh = newMesh;
}

void Entity::SetMesh(std::string meshName)
{
	mesh = AssetManager::Instance()->GetMesh(meshName);
}

void Entity::Update(double deltaTime)
{
}

void Entity::FixedUpdate(double fixedTime)
{
}

void Entity::RenderMesh(unsigned int * vertBuffer, unsigned int * uvBuffer)
{
	//	VERTEX BUFFER
	glGenBuffers(1, vertBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, *vertBuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(Vector3), &mesh->vertices[0], GL_STATIC_DRAW);

	//	UV BUFFER
	glGenBuffers(1, uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, *uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh->uvs.size() * sizeof(Vector2), &mesh->uvs[0], GL_STATIC_DRAW);

	glDrawArrays(GL_TRIANGLES, 0, mesh->VertCount);
}
