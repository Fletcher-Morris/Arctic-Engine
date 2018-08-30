#include "Camera.h"
#include "MatrixMaths.h"


void Camera::Configure(const CameraConfig & config)
{
	m_config = config;

	m_projMatrix = CreateProjMatrix(m_config);

	m_viewMatrix = CreateViewMatrix(*this);
	m_projViewMatrix = m_projMatrix * m_viewMatrix;
}

const Matrix4& Camera::GetViewMatrix()
{
	return m_viewMatrix;
}

const Matrix4& Camera::GetProjectionMatrix()
{
	return m_projMatrix;
}

const Matrix4& Camera::GetProjectionViewMatrix()
{
	return m_projViewMatrix;
}

void Camera::OnInit()
{
	m_config.farClip = 1000;
	m_config.fov = 70;
	m_config.height = 1080;
	m_config.nearClip = 0.1;
	m_config.width = 1920;
	Configure(m_config);
}

void Camera::OnUpdate(double deltaTime)
{
}

void Camera::OnFixedUpdate(double fixedTime)
{
}

void Camera::OnRender()
{
}

void Camera::OnEnable()
{
}

void Camera::OnDisable()
{
}
