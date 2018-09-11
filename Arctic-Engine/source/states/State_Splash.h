#pragma once
#include "State.h"

class State_Splash : public State {

public:

	State_Splash(Game& game);

	void HandleEvent	(int _event)			override;
	void HandleInput	(GLFWwindow* _window)	override;
	void Update			(double _deltaTime)		override;
	void FixedUpdate	(double _fixedTime)		override;
	void GuiUpdate()							override;
	void Render			(GLFWwindow* _target)	override;
};