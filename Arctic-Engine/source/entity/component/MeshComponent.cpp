#include "MeshComponent.h"

int yeet = 0;

void MeshComponent::OnInit()
{
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
