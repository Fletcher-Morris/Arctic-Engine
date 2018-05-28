#pragma once
#include "..\util\NonCopyable.h"
#include <glfw3.h>
#include "../render/Shader.h"

class Game;

class State
{
public:
	State(Game& game) :m_pGame(&game) {}

	virtual ~State() = default;

	virtual void HandleEvent	(int e) = 0;
	virtual void HandleInput	(GLFWwindow* window) = 0;
	virtual void Update			(double deltaTime) = 0;
	virtual void FixedUpdate	(double fixedTime) = 0;
	virtual void GuiUpdate		();
	virtual void Render			(GLFWwindow* target) = 0;

protected:
	Game * m_pGame;
};
