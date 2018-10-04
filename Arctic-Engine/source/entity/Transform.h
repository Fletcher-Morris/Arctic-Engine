#pragma once
#include "../util/GlmTypedefs.h"
#include <vector>

class Transform
{
public:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	void SetParent(Transform * _newParent);
	Transform * GetParent();

private:
	Transform * m_parent;
	std::vector<Transform*>m_children;
	//Vector3 position;
};