#pragma once
#include "../entity/ECS.h"

class Scene
{
public:
	Scene();
	~Scene();

	std::vector<std::unique_ptr<EcsEntity>> entities;
	int entityCount;

	void NewEntity(std::string _name);
	void NewEntity(std::string _name, std::string _meshName);
	void ClearEntities();

	void RefreshECS()
	{
		entities.erase(std::remove_if(std::begin(entities),
			std::end(entities), [](const std::unique_ptr<EcsEntity> &ent)
		{return ent->destroy; }), std::end(entities));
	}
};