#pragma once
#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "..\util\NonCopyable.h"

class Game;

class State : public NonCopyable
{
public:
	State(Game& game) :m_pGame(&game) {}

	virtual ~State() = default;

	virtual void HandleEvent	(sf::Event e) = 0;
	virtual void HandleInput	() = 0;
	virtual void Update			(sf::Time deltaTime) = 0;
	virtual void FixedUpdate	(sf::Time fixedTime) = 0;
	virtual void Render			(sf::RenderTarget& target) = 0;

protected:
	Game * m_pGame;
};

#endif // STATE_H_INCLUDED
