#pragma once

#include <memory>
#include <vector>
#include <array>
#include <bitset>

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


class EcsEntity
{
private:

	bool enabled = true;
	bool destroy = false;
	std::string name;
	std::vector<std::unique_ptr<EcsComponent>> components;
	CompArray componentArray;
	CompBits componentBits;

public:

	void SetName(std::string newName);
	std::string GetName() { return name; }

	bool IsEnabled() { return enabled; }
	void Destroy() { destroy = true; }

	void Update(double deltaTime) { for (auto& comp : components)comp->OnUpdate(deltaTime); }
	void FixedUpdate(double fixedTime) { for (auto& comp : components)comp->OnFixedUpdate(fixedTime); }
	void Render(int method) { for (auto& comp : components)comp->OnRender(method); };

	template<typename T>
	bool HasComponent()
	{
		return compBits[GetCompID<T>];
	}
};

class EcsComponent
{
public:
	EcsEntity * entity;
	virtual ~EcsComponent();

	virtual void OnInit();
	virtual void OnUpdate(double deltaTime);
	virtual void OnFixedUpdate(double fixedTime);
	virtual void OnRender(int method);
	virtual void OnEnable();
	virtual void OnDisable();

	bool uniquePerEntity;
};