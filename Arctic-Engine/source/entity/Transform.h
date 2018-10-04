#pragma once
#include "../util/GlmTypedefs.h"
#include <vector>
#include <iostream>

class Transform
{
public:
	Vector3 localPosition;
	Vector3 rotation;
	Vector3 scale;

	void SetParent(Transform * _newParent);
	Transform * GetParent();
	std::vector<Transform*>GetChildTransforms() { return m_children; }

	void UpdateInheritedTransform(Vector3 _inheritPosition)
	{
		std::cout << _inheritPosition.z << std::endl;
		m_inheritedPosition = _inheritPosition;
		m_worldPosition = m_inheritedPosition + localPosition;
		for (int i = 0; i < GetChildTransforms().size(); i++)
		{
			GetChildTransforms()[i]->UpdateInheritedTransform(m_worldPosition);
		}
	}
	Vector3 GetInheritedPosition() { return m_inheritedPosition; }
	Vector3 GetWorldPosition() { return m_worldPosition; }

private:
	Transform * m_parent;
	std::vector<Transform*>m_children;
	Vector3 m_inheritedPosition;
	Vector3 m_worldPosition;
};