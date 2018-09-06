#include "MeshRenderer.h"
#include "../Entity.h"

void MeshRenderer::SetMesh(Mesh * newMesh)
{
	mesh = newMesh;
}

void MeshRenderer::SetMesh(std::string meshName)
{
	mesh = AssetManager::Instance()->GetMesh(meshName);
}

void MeshRenderer::OnInit()
{
}

void MeshRenderer::OnUpdate(double deltaTime)
{
	std::cout << "MAH NAM IS " << entity->name;
}

void MeshRenderer::OnFixedUpdate(double fixedTime)
{
}

void MeshRenderer::OnRender(int method)
{
	if (!doRender) return;
	if (mesh == nullptr) return;
	mesh->Render(method);
}

void MeshRenderer::OnEnable()
{
}

void MeshRenderer::OnDisable()
{
}