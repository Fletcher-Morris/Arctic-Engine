#include "MeshRenderer.h"

void MeshRenderer::SetMesh(Mesh * newMesh)
{
	mesh = newMesh;
}

void MeshRenderer::SetMesh(std::string meshName)
{
	mesh = AssetManager::Instance()->GetMesh(meshName);
}

void MeshRenderer::RenderMesh(int method)
{
	if (!doRender) return;
	if (mesh == nullptr) return;
	mesh->Render(method);
}

void MeshRenderer::OnInit()
{
}

void MeshRenderer::OnUpdate(double deltaTime)
{
}

void MeshRenderer::OnFixedUpdate(double fixedTime)
{
}

void MeshRenderer::OnRender(int method)
{
	RenderMesh(0);
}

void MeshRenderer::OnEnable()
{
}

void MeshRenderer::OnDisable()
{
}