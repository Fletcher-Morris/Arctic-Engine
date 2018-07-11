#include "Entity.h"

Entity::Entity()
{
	name = "New Entity";
}

Entity::Entity(std::string _name)
{
	name = _name;
}

void Entity::Update(double deltaTime)
{
}

void Entity::FixedUpdate(double fixedTime)
{
}

void Entity::RenderMesh(unsigned int * vertBuffer, unsigned int * uvBuffer)
{

}
