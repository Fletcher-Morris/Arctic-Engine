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
	Transform newestEntity;

	EcsEntity& NewEntity(std::string _name)
	{
		EcsEntity* newEntity = new EcsEntity();
		newEntity->SetName(_name);
		newEntity->SetParent(&origin);
		std::unique_ptr<EcsEntity> uniquePtr{ newEntity };
		entities.emplace_back(std::move(uniquePtr));
		std::cout << "Created new entity '" << _name << "'" << std::endl;
		newestEntity = newEntity->transform;
		return *newEntity;
	}

	EcsEntity& NewEntity(std::string _name, std::string _meshName)
	{
		EcsEntity* newEntity = new EcsEntity();
		newEntity->SetName(_name);
		newEntity->SetParent(&origin);
		newEntity->AttachComponent<MeshComponent>();
		newEntity->GetComponent<MeshComponent>().SetMesh(_meshName);
		std::unique_ptr<EcsEntity> uniquePtr{ newEntity };
		entities.emplace_back(std::move(uniquePtr));
		std::cout << "Created new mesh entity '" << _name << "'" << std::endl;
		newestEntity = newEntity->transform;
		return *newEntity;
	}

	EcsEntity& NewEntity(std::string _name, std::string _meshName, Transform * _parent)
	{
		EcsEntity* newEntity = new EcsEntity();
		newEntity->SetName(_name);
		newEntity->SetParent(_parent);
		_parent->AddChild(&newEntity->transform);
		newEntity->AttachComponent<MeshComponent>();
		newEntity->GetComponent<MeshComponent>().SetMesh(_meshName);
		std::unique_ptr<EcsEntity> uniquePtr{ newEntity };
		entities.emplace_back(std::move(uniquePtr));
		std::cout << "Created new mesh entity '" << _name << "'" << std::endl;
		newestEntity = newEntity->transform;
		return *newEntity;
	}

	void ClearEntities() {
		for (auto& ent : entities) ent->Destroy(); entityCount = entities.size();
		newestEntity = origin;
	}

	void RefreshECS()
	{
		entities.erase(std::remove_if(std::begin(entities),
			std::end(entities), [](const std::unique_ptr<EcsEntity> &ent)
		{return ent->IsDestroyed(); }), std::end(entities));
		entityCount = entities.size();
	}

	int entityCount;



	void Save();
	void OnSceneLoad();

	Transform origin;

private:
	std::string m_savePath;
	bool m_isfullyLoaded;
};