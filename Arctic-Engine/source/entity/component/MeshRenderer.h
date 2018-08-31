#include "../Mesh.h"
#include "../Component.h"
#include "../../util/AssetManager.h"

class MeshRenderer : public Component
{
public:
	Mesh * mesh;
	void SetMesh(Mesh * newMesh);
	void SetMesh(std::string meshName);
	Mesh * GetMesh() { return mesh; }

	bool doRender;

	// Inherited via Component
	virtual void OnInit() override;
	virtual void OnUpdate(double deltaTime) override;
	virtual void OnFixedUpdate(double fixedTime) override;
	virtual void OnRender(int method) override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;

private:
	void RenderMesh(int method);
};