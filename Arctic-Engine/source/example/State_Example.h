#pragma once
#include "../states/State.h"

class State_Example : public State {

public:

	State_Example(Game& game);

	void HandleEvent(sf::Event e)		override;
	void HandleInput()					override;
	void Update(double deltaTime)		override;
	void FixedUpdate(double deltaTime)	override;
	void Render(GLFWwindow* target)		override;
};