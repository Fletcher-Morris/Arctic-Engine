#pragma once
#include "../util/GlmTypedefs.h"

struct Vertex
{
	Vector3 position;
	Vector3 normal;
	Vector2 uv;
};

struct IndexTriplet
{
	int pos, uv, norm;
};