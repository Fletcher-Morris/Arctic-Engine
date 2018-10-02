#pragma once
#include "../util/GlmTypedefs.h"

class Transform
{
public:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	Transform * parent;

private:
	std::vector<Transform*>m_children;
};