#pragma once
#include "State.h"

class State_Splash : public State {

public:

	State_Splash(Game& game);

	void HandleEvent	(sf::Event e)					override;
	void HandleInput()									override;
	void Update			(sf::Time deltaTime)			override;
	void FixedUpdate	(sf::Time deltaTime)			override;
	void Render			(sf::RenderTarget& target)	override;
};