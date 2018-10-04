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

constexpr std::size_t MAX_ENTITY_COMPONENTS = 16;

inline std::size_t GetCompID()
{
	static std::size_t prevId = 0;
	return prevId++;
}
template <typename T>
inline std::size_t GetCompID() noexcept
{
	static std::size_t id = GetCompID();
	return id;
}


class EcsComponent
{
private:

	bool m_enabled = true;
	bool m_uniquePreEntity = false;

public:

	EcsEntity * entity;
	virtual ~EcsComponent() {}

	bool IsEnabled() { return m_enabled; }
	void Enable() { if (!m_enabled) { m_enabled = true; OnEnable(); } }
	void Disable() { if (m_enabled) { m_enabled = false; OnDisable(); } }
	bool IsUnique() { return m_uniquePreEntity; }

	virtual void OnInit() {}
	virtual void OnUpdate(double _deltaTime) {}
	virtual void OnFixedUpdate(double _fixedTime) {}
	virtual void OnRender(int _method) {}
	virtual void OnEnable() {}
	virtual void OnDisable() {}
};


class EcsEntity
{
private:
	std::string m_name;
	bool m_destroy = false;
	bool m_enabled = true;
	std::vector<std::unique_ptr<EcsComponent>> m_components;
	std::array<EcsComponent*, MAX_ENTITY_COMPONENTS> m_componentArray;
	std::bitset<MAX_ENTITY_COMPONENTS> m_componentBits;

public:
	Transform transform;
	void SetParent(Transform * _newParent) { transform.SetParent(_newParent); };
	Transform * GetParent() { return transform.GetParent(); };

	void SetName(std::string _name) { m_name = _name; }
	std::string GetName() { return m_name; }
	
	bool IsEnabled() { return m_enabled; }
	void Destroy() { m_destroy = true; }
	bool IsDestroyed() { return m_destroy; }

	void Update(double _deltaTime) { for (auto& comp : m_components)comp->OnUpdate(_deltaTime); }
	void FixedUpdate(double _fixedTime) { for (auto& comp : m_components)comp->OnFixedUpdate(_fixedTime); }
	void Render(int _method) { for (auto& comp : m_components)comp->OnRender(_method); };

	template<typename T>
	bool HasComponent()
	{
		return m_componentBits[GetCompID<T>];
	}

	template<typename T, typename... args>
	T& AttachComponent(args&&... _args)
	{
		T* newComponent(new T(std::forward<args>(_args)...));
		newComponent->entity = this;
		std::unique_ptr<EcsComponent> uniquePtr{ newComponent };
		m_components.emplace_back(std::move(uniquePtr));
		m_componentArray[GetCompID<T>()] = newComponent;
		m_componentBits[GetCompID<T>()] = true;
		newComponent->OnInit();
		return *newComponent;
	}

	template<typename T>
	T& GetComponent()
	{
		auto ptr(m_componentArray[GetCompID<T>()]);
		return *static_cast<T*>(ptr);
	}
};