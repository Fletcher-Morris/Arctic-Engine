#pragma once
#include "../entity/Entity.h"
#include <list>

class Scene
{

public:
	Scene();
	~Scene();

	std::list<Entity> entList;
	std::vector<Entity> entVec;
	int entityCount;

	void NewEntity(std::string _name);
};