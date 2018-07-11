#pragma once

#include "../util/GlmTypedefs.h"
#include "../util/OtherTypedefs.h"
#include "Mesh.h"

class Entity
{
public:

	Entity();
	Entity(std::string _name);

	string name;
	Vector3 position;
	Vector3 rotation;
	Mesh * mesh;

	void SetMesh(Mesh * newMesh) { mesh = newMesh; }
	Mesh * GetMesh() { return mesh; }
};