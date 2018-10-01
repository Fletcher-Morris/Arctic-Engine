#pragma once
#include "State.h"

class State_Editor : public State
{
public:
	State_Editor();
	~State_Editor();

	// Inherited via State
	virtual void HandleEvent	(int _event)			override;
	virtual void HandleInput	(GLFWwindow * _window)	override;
	virtual void Update			(double _deltaTime)		override;
	virtual void FixedUpdate	(double _fixedTime)		override;
	virtual void GuiUpdate		()						override;
	virtual void Render			(GLFWwindow * _target)	override;
};