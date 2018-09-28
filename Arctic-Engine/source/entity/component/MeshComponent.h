#pragma once

#include "../ECS.h"
#include "../Mesh.h"
#include "../../util/AssetManager.h"
#include "../../render/Shader.h"
#include "../../render/Material.h"

class MeshComponent : public EcsComponent
{
public:

	// Inherited via EcsComponent
	virtual void OnInit() override;
	virtual void OnUpdate(double _deltaTime) override;
	virtual void OnFixedUpdate(double _fixedTime) override;
	virtual void OnRender(int _method) override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;

	void SetMesh(Mesh * _mesh);
	void SetMesh(std::string _name);
	Mesh * GetMesh() { return m_mesh; }
	void SetShader(Shader * _shader);

	void SetMaterial(Material * _material);
	void SetMaterial(std::string _materialName);
	Material * GetMaterial() { return m_material; }

	bool doRender = true;

private:
	Mesh * m_mesh;
	Material * m_material;
	Shader * m_shader;
	void UpdateShaderMatrix();
};