#include "MeshComponent.h"

int lol = 1;
int yeet = 1;

void MeshComponent::OnInit()
{
	m_shader = AssetManager::Instance()->GetShader("standard");
	entity->transform.position.z = 2.0f;
}

void MeshComponent::OnUpdate(double deltaTime)
{
	if (entity->transform.position.x >= 2.0f)
	{
		lol = -1;
	}
	else if (entity->transform.position.x <= -2.0f)
	{
		lol = 1;
	}
	if (entity->transform.position.y >= 2.0f)
	{
		yeet = -1;
	}
	else if (entity->transform.position.y <= -2.0f)
	{
		yeet = 1;
	}

	entity->transform.position.y += deltaTime * 0.015f * yeet;
	entity->transform.position.x += deltaTime * 0.05f * lol;
}

void MeshComponent::OnFixedUpdate(double fixedTime)
{
}

void MeshComponent::OnRender(int method)
{
	if (!doRender) return;
	if (m_mesh == nullptr) return;
	if (m_shader == nullptr) return;

	m_shader->Bind();
	UpdateShaderMatrix();
	m_mesh->Render(method);
}

void MeshComponent::OnEnable()
{
}

void MeshComponent::OnDisable()
{
}

void MeshComponent::SetMesh(Mesh * newMesh)
{
	m_mesh = newMesh;
}

void MeshComponent::SetMesh(std::string meshName)
{
	m_mesh = AssetManager::Instance()->GetMesh(meshName);
}

void MeshComponent::SetShader(Shader * _shader)
{
	m_shader = _shader;
}

void MeshComponent::UpdateShaderMatrix()
{
	Matrix4 model = Matrix4(1.0f);
	Matrix4 view = glm::lookAt(
		entity->transform.position,
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	Matrix4 proj = glm::perspective(glm::radians(60.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);

	Matrix4 mvp = proj * view * model;

	m_shader->SetMvpMatrix(mvp);
}