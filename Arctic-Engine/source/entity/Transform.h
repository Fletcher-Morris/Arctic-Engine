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

	void SetParent(Transform * _newParent)
	{
		if (m_parent != _newParent)
		{
			m_parent = _newParent;
			if (!_newParent->HasChild(this))
			{
				m_parent->AddChild(this);
			}
		}
	}
	Transform * GetParent() { return m_parent; }
	std::vector<Transform*>GetChildTransforms() { return m_children; }
	bool HasChild(Transform * _child)
	{
		for (int i = 0; i < m_childCount; i++)
		{
			if (m_children[i] == _child)
			{
				return true;
			}
		}
		return false;
	}
	void AddChild(Transform * _child)
	{
		if (!HasChild(_child))
		{
			m_children.push_back(_child);
			m_childCount++;
		}
		else if (_child->GetParent() != this)
		{
			_child->SetParent(this);
		}
	}

	void UpdateInheritedTransform(Vector3 _inheritPosition)
	{
		//std::cout << _inheritPosition.z << std::endl;
		m_inheritedPosition = _inheritPosition;
		m_worldPosition = m_inheritedPosition + localPosition;
		for (int i = 0; i < m_childCount; i++)
		{
			std::cout << "Sending inherited transform position " << m_worldPosition.z << std::endl;
			GetChildTransforms()[i]->UpdateInheritedTransform(m_worldPosition);
		}
	}
	Vector3 GetInheritedPosition() { return m_inheritedPosition; }
	Vector3 GetWorldPosition() { return m_worldPosition; }

private:
	Transform * m_parent;
	std::vector<Transform*>m_children;
	int m_childCount;
	Vector3 m_inheritedPosition;
	Vector3 m_worldPosition;
};