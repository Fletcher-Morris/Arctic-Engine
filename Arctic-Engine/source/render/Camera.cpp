#include "Camera.h"
#include "MatrixMaths.h"

Camera::Camera(const CameraConfig & config) : m_config (config)
{
	m_projMatrix = CreateProjMatrix(config);
}

Camera::Camera()
{
	CameraConfig config;
	config.farClip = 1000;
	config.fov = 70;
	config.height = 1080;
	config.nearClip = 0.1;
	config.width = 1920;

	m_projMatrix = CreateProjMatrix(config);
}

void Camera::Update()
{
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
