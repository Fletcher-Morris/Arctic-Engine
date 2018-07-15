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

void Entity::RenderMesh()
{
	if (!doRender) return;

	mesh->Render();
}