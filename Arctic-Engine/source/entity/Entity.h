#pragma once

#include "../util/GlmTypedefs.h"
#include "../util/OtherTypedefs.h"
#include "../core/Obj.h"

struct Entity
{
	string name;
	Vector3 position;
	Vector3 rotation;
	Obj * mesh;

	void SetMesh(Obj * newMesh) { mesh = newMesh; }
	Obj * GetMesh() { return mesh; }
};