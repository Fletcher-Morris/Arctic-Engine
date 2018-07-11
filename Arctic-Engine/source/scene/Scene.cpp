#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::NewEntity(std::string _name)
{
	entList.push_back(Entity(_name));
	entVec.push_back(Entity(_name));
	entityCount++;
}