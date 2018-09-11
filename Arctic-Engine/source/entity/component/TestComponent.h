#pragma once
#include "../ECS.h"

class TestComponent : public EcsComponent
{
public:
	// Inherited via EcsComponent
	virtual void OnInit() override;
	virtual void OnUpdate(double deltaTime) override;
	virtual void OnFixedUpdate(double fixedTime) override;
	virtual void OnRender(int method) override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
};