#include "../Entity.h"
#include "../Component.h"

class MeshRenderer : public Component
{
	// Inherited via Component
	virtual void OnInit() override;
	virtual void OnUpdate(double deltaTime) override;
	virtual void OnFixedUpdate(double fixedTime) override;
	virtual void OnRender() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
};