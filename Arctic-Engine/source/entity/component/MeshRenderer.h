#include "../Mesh.h"
#include "../../util/AssetManager.h"
#include "../ECS.h"

class MeshRenderer : public EcsComponent
{
public:
	Mesh * mesh;
	void SetMesh(Mesh * newMesh);
	void SetMesh(std::string meshName);
	Mesh * GetMesh() { return mesh; }
	bool doRender = true;

	// Inherited via EcsComponent
	virtual void OnInit() override;
	virtual void OnUpdate(double deltaTime) override;
	virtual void OnFixedUpdate(double fixedTime) override;
	virtual void OnRender(int method) override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
};