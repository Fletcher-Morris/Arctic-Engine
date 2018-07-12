#pragma once
#include "../entity/Entity.h"
#include <list>

class Scene
{

public:
	Scene();
	~Scene();

	std::vector<Entity> entVec;
	int entityCount;

	void NewEntity(std::string _name);
};