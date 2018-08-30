#pragma once

class Component
{
public:
	Component();
	virtual ~Component() = default;

	virtual void OnInit() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnFixedUpdate() = 0;
	virtual void OnRender() = 0;
	virtual void OnEnable() = 0;
	virtual void OnDisable() = 0;
};