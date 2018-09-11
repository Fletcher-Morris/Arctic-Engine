#pragma once
#include "../states/State.h"
#include "../scene/Scene.h"

class State_Example : public State {

public:

	State_Example(Game& _game);

	void HandleEvent	(int _event)			override;
	void HandleInput	(GLFWwindow* _window)	override;
	void Update			(double _deltaTime)		override;
	void FixedUpdate	(double _fixedTime)		override;
	void GuiUpdate()							override;
	void Render			(GLFWwindow* _target)	override;

	Scene currentScene;
};