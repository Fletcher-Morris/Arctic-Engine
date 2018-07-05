#pragma once
#include "../util/GlmTypedefs.h"
#include <vector>

struct Mesh
{
public:
	std::vector	<Vector3> vertices;
	std::vector	<Vector2> uvs;
	std::vector	<Vector3> normals;
};

