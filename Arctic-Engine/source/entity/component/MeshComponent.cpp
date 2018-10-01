#include "MeshComponent.h"


void MeshComponent::OnInit()
{
	m_shader = AssetManager::Instance()->GetShader("standard");
	entity->transform.position.z = -1.5f;
}

void MeshComponent::OnUpdate(double deltaTime)
{
	entity->transform.rotation.y += deltaTime * 0.01f;
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

void MeshComponent::SetMaterial(Material * _material)
{
	m_material = _material;
}
void MeshComponent::SetMaterial(std::string _materialName)
{
	m_material = AssetManager::Instance()->GetMaterial(_materialName);
}

void MeshComponent::UpdateShaderMatrix()
{
	Matrix4 projection = glm::perspective(glm::radians(60.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
	Matrix4 translation = glm::translate(projection, entity->transform.position);

	Matrix4 yRotation = glm::rotate(translation, entity->transform.rotation.y, Vector3(0.0f, 1.0f, 0.0f));
	Matrix4 xRotation = glm::rotate(yRotation, entity->transform.rotation.x, Vector3(1.0f, 0.0f, 0.0f));
	Matrix4 zRotation = glm::rotate(xRotation, entity->transform.rotation.z, Vector3(0.0f, 0.0f, 1.0f));

	m_shader->SetMvpMatrix(zRotation);
}