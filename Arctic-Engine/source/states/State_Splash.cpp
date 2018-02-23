#include "State_Splash.h"
#include "../core/Game.h"
#include "../core/Obj.h"
#include "../example/State_Example.h"
#include <iostream>

sf::Clock timer;
sf::Sprite splash;

State_Splash::State_Splash(Game& game) : State(game) {

	std::cout << "Entered state: (State_Splash)" << std::endl;

	game.assets.LoadTexture("ArcticSplash", "assets/textures/ArcticSplash.jpg");
	splash = sf::Sprite(game.assets.GetTexture("ArcticSplash"));
	splash.setPosition(0, 0);
	timer.restart();
}

void State_Splash::HandleEvent(sf::Event e) {
	glfwPollEvents();
}

void State_Splash::HandleInput(GLFWwindow* window) {

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void State_Splash::Update(double deltaTime) {

	if (timer.getElapsedTime().asSeconds() >= 3) {
		m_pGame->PushState<State_Example>(*m_pGame);
	}
}

void State_Splash::FixedUpdate(double fixedTime) {

}

void State_Splash::Render(GLFWwindow* target) {
	Game* m_game = (Game*)glfwGetWindowUserPointer(target);
}