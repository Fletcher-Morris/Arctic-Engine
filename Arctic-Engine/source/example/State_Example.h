#pragma once
#include "../states/State.h"

#include "../scene/Scene.h"
#include "../render/Camera.h"
#include "../entity/component/MeshRenderer.h"

class State_Example : public State {

public:

	State_Example(Game& game);

	void HandleEvent	(int e)			override;
	void HandleInput	(GLFWwindow* window)	override;
	void Update			(double deltaTime)		override;
	void FixedUpdate	(double deltaTime)		override;
	void GuiUpdate()							override;
	void Render			(GLFWwindow* target)	override;

	Scene currentScene;
};