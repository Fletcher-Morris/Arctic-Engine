#include "Entity.h"

Entity::Entity()
{
	name = "New Entity";
}

Entity::Entity(std::string _name)
{
	name = _name;
}

void Entity::SetName(std::string newName)
{
	name = newName;
}

std::string Entity::GetName()
{
	return name;
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

void Entity::Render(int method)
{
	for (int i = 0; i < m_components.size(); i++)
	{
		m_components[i]->OnRender(method);
	}
}