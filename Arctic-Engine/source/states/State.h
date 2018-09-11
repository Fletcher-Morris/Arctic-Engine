#pragma once
#include "..\util\NonCopyable.h"
#include <glfw3.h>
#include "../render/Shader.h"

class Game;

class State
{
public:
	State(Game& _game) :p_game(&_game) {}

	virtual ~State() = default;

	virtual void HandleEvent	(int _event) = 0;
	virtual void HandleInput	(GLFWwindow* _window) = 0;
	virtual void Update			(double _deltaTime) = 0;
	virtual void FixedUpdate	(double _fixedTime) = 0;
	virtual void GuiUpdate		();
	virtual void Render			(GLFWwindow* _target) = 0;

protected:
	Game * p_game;
};
