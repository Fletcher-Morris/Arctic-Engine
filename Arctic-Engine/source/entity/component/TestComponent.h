#pragma once
#include "../ECS.h"

class TestComponent : public EcsComponent
{
public:
	// Inherited via EcsComponent
	virtual void OnInit() override;
	virtual void OnUpdate(double _deltaTime) override;
	virtual void OnFixedUpdate(double _fixedTime) override;
	virtual void OnRender(int _method) override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
};