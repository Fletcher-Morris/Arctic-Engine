#include "MeshComponent.h"

int yeet = 0;

void MeshComponent::OnInit()
{
	m_shader = AssetManager::Instance()->GetShader("standard");
}

void MeshComponent::OnUpdate(double deltaTime)
{
}

void MeshComponent::OnFixedUpdate(double fixedTime)
{
}

void MeshComponent::OnRender(int method)
{
	yeet++;
	if (yeet >= 50)
	{
		doRender = !doRender;
		yeet = 0;
	}

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
		glm::vec3(1.2f, 1.2f, 1.2f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f));
	Matrix4 proj = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);

	Matrix4 mvp = proj * view * model;

	m_shader->SetMvpMatrix(mvp);
}