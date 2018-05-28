#pragma once
#include "../states/State.h"

class State_Example : public State {

public:

	State_Example(Game& game);

	void HandleEvent	(int e)			override;
	void HandleInput	(GLFWwindow* window)	override;
	void Update			(double deltaTime)		override;
	void FixedUpdate	(double deltaTime)		override;
	void GuiUpdate()							override;
	void Render			(GLFWwindow* target)	override;
};