#include "CameraComponent.h"

void CameraComponent::OnInit()
{
}

void CameraComponent::OnUpdate(double deltaTime)
{
}

void CameraComponent::OnFixedUpdate(double fixedTime)
{
}

void CameraComponent::OnRender(int method)
{
}

void CameraComponent::OnEnable()
{
}

void CameraComponent::OnDisable()
{
}

void CameraComponent::Configure(const CameraConfig & config)
{
	m_config = config;
	m_projMatrix = CreateProjMatrix(m_config);
	m_viewMatrix = CreateViewMatrix(*this);
	m_projViewMatrix = m_projMatrix * m_viewMatrix;
}
