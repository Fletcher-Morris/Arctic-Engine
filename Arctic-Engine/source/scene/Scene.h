#pragma once
#include "../entity/Entity.h"

class Scene
{

public:
	Scene();
	~Scene();

	std::vector<Entity> entities;
	int entityCount;

	void NewEntity(std::string _name);
	void NewEntity(std::string _name, std::string _meshName);
	void ClearEntities();
};