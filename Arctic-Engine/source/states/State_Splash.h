#pragma once
#include "State.h"

class State_Splash : public State {

public:

	State_Splash(Game& game);

	void HandleEvent	(sf::Event e)			override;
	void HandleInput()							override;
	void Update			(double deltaTime)		override;
	void FixedUpdate	(double deltaTime)		override;
	void Render			(GLFWwindow* target)		override;
};