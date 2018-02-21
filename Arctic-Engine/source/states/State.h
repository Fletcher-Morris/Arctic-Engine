#pragma once
#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "..\util\NonCopyable.h"
#include <glfw3.h>

class Game;

class State : public NonCopyable
{
public:
	State(Game& game) :m_pGame(&game) {}

	virtual ~State() = default;

	virtual void HandleEvent	(sf::Event e) = 0;
	virtual void HandleInput	(GLFWwindow* window) = 0;
	virtual void Update			(double deltaTime) = 0;
	virtual void FixedUpdate	(double fixedTime) = 0;
	virtual void Render			(GLFWwindow* target) = 0;

protected:
	Game * m_pGame;
};

#endif // STATE_H_INCLUDED
