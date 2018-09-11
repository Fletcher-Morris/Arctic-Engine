#pragma once
#include "../util/GlmTypedefs.h"

class Transform
{
public:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	Vector3 up			=	{ 0, 1, 0 };
	Vector3 down		=	{ 0,-1, 0 };
	Vector3 right		=	{ 1, 0, 0 };
	Vector3 left		=	{-1, 0, 0 };
	Vector3 forward		=	{ 0, 0, 1 };
	Vector3 back		=	{ 0, 0,-1 };
};