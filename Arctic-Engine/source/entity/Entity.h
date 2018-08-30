#pragma once

#include "../util/GlmTypedefs.h"
#include "../util/OtherTypedefs.h"
#include "Component.h"
#include "Mesh.h"
#include "../util/AssetManager.h"
#include <typeinfo>

class Entity
{
private:
	std::vector<Component*> m_components;

public:

	Entity();
	Entity(std::string _name);
	Entity(std::string _name, std::string _meshName);

	string name;
	Vector3 position;
	Vector3 rotation;
	Mesh * mesh;

	bool doRender;

	void SetMesh(Mesh * newMesh);
	void SetMesh(std::string meshName);
	Mesh * GetMesh() { return mesh; }

	void Update(double deltaTime);
	void FixedUpdate(double fixedTime);
	void RenderMesh(int method);

	template<class T>
	void AttachComponent()
	{
		m_components.push_back(new T);
		std::cout << "Attached '" << typeid(T).name() << "' to entity '" << name << "'" << std::endl;
	}

	template<class T>
	void DetachComponent()
	{
		for (int i = 0; i < m_components.size(); i++)
		{
			if (typeid(*m_components[i]).name() == typeid(T).name())
			{
				std::cout << "Detached '" << typeid(T).name() << "' from entity '" << name << "'" << std::endl;
				m_components.erase(m_components.begin() + i);
			}
		}
	}
};