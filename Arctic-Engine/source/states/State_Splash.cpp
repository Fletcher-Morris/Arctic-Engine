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

}

void State_Splash::FixedUpdate(double fixedTime) {

}

void State_Splash::Render(GLFWwindow* target) {

	if (timer.getElapsedTime().asSeconds() >= 3) {
		m_pGame->PushState<State_Example>(*m_pGame);
	}

	float positions[6] = {
		-0.5f, -0.5f,
		0.0f,  0.5f,
		0.5f, -0.5f
	};

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	glClearColor(0.0f, 0.5647f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}