#pragma once
#include "../states/State.h"

class State_Example : public State {

public:

	State_Example(Game& game);

	void HandleEvent(sf::Event e)			override;
	void HandleInput()						override;
	void Update(sf::Time deltaTime)			override;
	void FixedUpdate(sf::Time deltaTime)	override;
	void Render(sf::RenderTarget& target)	override;
};