#pragma once

#include <memory>
#include <vector>
#include <array>
#include <bitset>
#include <algorithm>
#include <iostream>

#include "Transform.h"

class EcsEntity;
class EcsComponent;

using CompID = std::size_t;
constexpr CompID MAX_ENTITY_COMPONENTS = 16;
using CompBits = std::bitset<MAX_ENTITY_COMPONENTS>;
using CompArray = std::array<EcsComponent*, MAX_ENTITY_COMPONENTS>;

inline CompID GetCompID()
{
	static CompID prevId = 0;
	return prevId++;
}
template <typename T>
inline CompID GetCompID() noexcept
{
	static CompID id = GetCompID();
	return id;
}


class EcsComponent
{
private:

	bool enabled = true;
	bool uniquePerEntity = false;

public:

	EcsEntity * entity;
	virtual ~EcsComponent();

	void Enable() { if (!enabled) { enabled = true; OnEnable(); } }
	void Disable() { if (enabled) { enabled = false; OnDisable(); } }

	virtual void OnInit() = 0;
	virtual void OnUpdate(double deltaTime) = 0;
	virtual void OnFixedUpdate(double fixedTime) = 0;
	virtual void OnRender(int method) = 0;
	virtual void OnEnable() = 0;
	virtual void OnDisable() = 0;
};


class EcsEntity
{
private:
	std::string name;
	std::vector<std::unique_ptr<EcsComponent>> components;
	CompArray componentArray;
	CompBits componentBits;

public:

	void SetName(std::string newName) { name = newName; }
	std::string GetName() { return name; }

	bool enabled = true;
	bool destroy = false;
	bool IsEnabled() { return enabled; }
	void Destroy() { destroy = true; }

	Transform transform;

	void Update(double deltaTime)
	{
		for (auto& comp : components)comp->OnUpdate(deltaTime);
	}
	void FixedUpdate(double fixedTime) { for (auto& comp : components)comp->OnFixedUpdate(fixedTime); }
	void Render(int method) { for (auto& comp : components)comp->OnRender(method); };

	template<typename T>
	bool HasComponent()
	{
		return compBits[GetCompID<T>];
	}

	template<typename T, typename... args>
	T& AttachComponent(args&&... mArguments)
	{
		T* newComponent(new T(std::forward<args>(mArguments)...));
		newComponent->entity = this;
		std::unique_ptr<EcsComponent> uniquePtr{ newComponent };
		components.emplace_back(std::move(uniquePtr));
		componentArray[GetCompID<T>()] = newComponent;
		componentBits[GetCompID<T>()] = true;
		newComponent->OnInit();
		return *newComponent;
	}

	template<typename T>
	T& GetComponent()
	{
		auto ptr(componentArray[GetCompID<T>()]);
		return *static_cast<T*>(ptr);
	}
};