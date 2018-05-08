#pragma once
#include "State.h"

class State_Splash : public State {

public:

	State_Splash(Game& game);

	void HandleEvent	(int e)			override;
	void HandleInput	(GLFWwindow* window)	override;
	void Update			(double deltaTime)		override;
	void FixedUpdate	(double deltaTime)		override;
	void GuiUpdate()							override;
	void Render			(GLFWwindow* target)	override;
};