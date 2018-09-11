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
	if (mesh == nullptr) return;
	mesh->Render(method);
}

void MeshComponent::OnEnable()
{
}

void MeshComponent::OnDisable()
{
}

void MeshComponent::SetMesh(Mesh * newMesh)
{
	mesh = newMesh;

}

void MeshComponent::SetMesh(std::string meshName)
{
	mesh = AssetManager::Instance()->GetMesh(meshName);
}
