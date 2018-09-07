#pragma once
#include "../entity/ECS.h"
#include "../entity/component/MeshRenderer.h"

class Scene
{
public:
	Scene();
	~Scene();

	std::vector<std::unique_ptr<EcsEntity>> entities;

	EcsEntity& NewEntity(std::string _name)
	{
		EcsEntity* newEntity = new EcsEntity();
		newEntity->SetName(_name);
		std::unique_ptr<EcsEntity> uniquePtr{ newEntity };
		entities.emplace_back(std::move(uniquePtr));
		std::cout << "Created new entity '" << _name << "'" << std::endl;
		return *newEntity;
	}

	EcsEntity& NewEntity(std::string _name, std::string _meshName)
	{
		EcsEntity* newEntity = new EcsEntity();
		newEntity->SetName(_name);
		newEntity->AttachComponent<MeshRenderer>();
		newEntity->GetComponent<MeshRenderer>().SetMesh(_meshName);
		std::unique_ptr<EcsEntity> uniquePtr{ newEntity };
		entities.emplace_back(std::move(uniquePtr));
		std::cout << "Created new mesh entity '" << _name << "'" << std::endl;
		return *newEntity;
	}

	void ClearEntities() { for (auto& ent : entities) ent->Destroy(); }

	void RefreshECS()
	{
		entities.erase(std::remove_if(std::begin(entities),
			std::end(entities), [](const std::unique_ptr<EcsEntity> &ent)
		{return ent->destroy; }), std::end(entities));
	}
};