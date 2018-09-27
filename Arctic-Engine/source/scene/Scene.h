#pragma once
#include "../entity/ECS.h"
#include "../entity/component/MeshComponent.h"
#include "../entity/component/CameraComponent.h"
#include "../entity/component/TestComponent.h"


class Scene
{
public:
	Scene();
	~Scene();

	std::vector<std::unique_ptr<EcsEntity>> entities;
	EcsEntity * mainCamera;

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
		newEntity->AttachComponent<MeshComponent>();
		newEntity->GetComponent<MeshComponent>().SetMesh(_meshName);
		std::unique_ptr<EcsEntity> uniquePtr{ newEntity };
		entities.emplace_back(std::move(uniquePtr));
		std::cout << "Created new mesh entity '" << _name << "'" << std::endl;
		return *newEntity;
	}

	void ClearEntities() { for (auto& ent : entities) ent->Destroy(); entityCount = entities.size(); }

	void RefreshECS()
	{
		entities.erase(std::remove_if(std::begin(entities),
			std::end(entities), [](const std::unique_ptr<EcsEntity> &ent)
		{return ent->IsDestroyed(); }), std::end(entities));
		entityCount = entities.size();
	}

	int entityCount;
};