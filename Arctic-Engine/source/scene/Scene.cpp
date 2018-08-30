#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::NewEntity(std::string _name)
{
	entities.push_back(Entity(_name));
	entityCount++;
	std::cout << "Created new entity '" << _name << "'" << std::endl;
}

void Scene::ClearEntities()
{
	entities.clear();
	std::cout << "Cleared " << entityCount << " entities" << std::endl;
	entityCount = 0;
}
