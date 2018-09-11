#pragma once
#include "../ECS.h"
#include "../../render/CameraConfig.h"
#include "../../util/GlmTypedefs.h"
#include "../../render/MatrixMaths.h"

class CameraComponent : public EcsComponent
{
public:

	// Inherited via EcsComponent
	virtual void OnInit() override;
	virtual void OnUpdate(double _deltaTime) override;
	virtual void OnFixedUpdate(double _fixedTime) override;
	virtual void OnRender(int _method) override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;

	void Configure(const CameraConfig& _config);
	const Matrix4& GetViewMatrix() { return m_viewMatrix; }
	const Matrix4& GetProjectionMatrix() { return m_projMatrix; }
	const Matrix4& GetProjectionViewMatrix() { return m_projViewMatrix; }

private:
	CameraConfig m_config;
	Matrix4 m_projMatrix;
	Matrix4 m_viewMatrix;
	Matrix4 m_projViewMatrix;
};