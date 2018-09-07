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

void Scene::NewEntity(std::string _name, std::string _meshName)
{
	Entity newEnt = Entity(_name);
	newEnt.AttachComponent<MeshRenderer>();
	newEnt.GetComponent<MeshRenderer>()->SetMesh(_meshName);
	entities.push_back(newEnt);
	entityCount++;
	std::cout << "Created new mesh entity '" << _name << "'" << std::endl;
}

void Scene::ClearEntities()
{
	for (auto& ent : entities) ent->Destroy();
	std::cout << "Cleared " << entityCount << " entities" << std::endl;
	entityCount = 0;
}
