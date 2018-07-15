#pragma once

#include "../util/GlmTypedefs.h"
#include "../util/OtherTypedefs.h"
#include "Mesh.h"
#include "../util/AssetManager.h"

class Entity
{
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
	void RenderMesh();
};