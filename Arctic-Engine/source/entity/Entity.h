#pragma once

#include <typeinfo>
#include "../util/OtherTypedefs.h"
#include "../util/AssetManager.h"
#include "Transform.h"

#include "component\MeshRenderer.h"

class Entity
{
private:
	std::vector<Component*> m_components;

public:

	Entity();
	Entity(std::string _name);

	string name;
	Transform transform;

	void Update(double deltaTime);
	void FixedUpdate(double fixedTime);
	void Render(int method);

	template<class T>
	void AttachComponent()
	{
		Component * newComp(new T);
		if (&newComp->uniquePerEntity && this->HasComponent<T>())
		{
			std::cout << "Component '" << typeid(T).name() << "' is already attached to entity '" << name << "'" << std::endl;
			return;
		}
		m_components.push_back(newComp);
		std::cout << "Attached '" << typeid(T).name() << "' to entity '" << name << "'" << std::endl;
	}

	template<class T>
	void DetachComponent()
	{
		bool detached = false;
		for (int i = 0; i < m_components.size(); i++)
		{
			if (typeid(*m_components[i]).name() == typeid(T).name())
			{
				std::cout << "Detached '" << typeid(T).name() << "' from entity '" << name << "'" << std::endl;
				m_components.erase(m_components.begin() + i);
				detached = true;
			}
		}
		if (!detached)
		{
			std::cout << "Could not detach '" << typeid(T).name() << "' from entity '" << name << "'" << std::endl;
		}
	}

	template<class T>
	T * GetComponent()
	{
		for (int i = 0; i < m_components.size(); i++)
		{
			if (typeid(*m_components[i]).name() == typeid(T).name())
			{
				return (T*)m_components[i];
			}
		}
		std::cout << "Could not find '" << typeid(T).name() << "' on entity '" << name << "'" << std::endl;
	}

	template<class T>
	bool HasComponent()
	{
		for (int i = 0; i < m_components.size(); i++)
		{
			if (typeid(*m_components[i]).name() == typeid(T).name())
			{
				return true;
			}
		}
		return false;
	}
};