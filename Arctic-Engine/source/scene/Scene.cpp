#include "Scene.h"

Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::ClearEntities()
{
	for (auto& ent : entities) ent->Destroy();
	std::cout << "Cleared " << entityCount << " entities" << std::endl;
	entityCount = 0;
}
