#pragma once
#include "../entity/Entity.h"

class Scene
{

public:
	Scene();
	~Scene();

	std::vector<Entity> entities;
};