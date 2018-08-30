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
	for (int i = 0; i < m_components.size(); i++)
	{
		m_components[i]->OnUpdate(deltaTime);
	}
}

void Entity::FixedUpdate(double fixedTime)
{
	for (int i = 0; i < m_components.size(); i++)
	{
		m_components[i]->OnFixedUpdate(fixedTime);
	}
}

void Entity::RenderMesh(int method)
{
	if (!doRender) return;

	mesh->Render(method);
}