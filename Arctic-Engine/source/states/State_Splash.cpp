#include "State_Splash.h"
#include "../core/Game.h"
#include "../core/Obj.h"
#include "../example/State_Example.h"
#include <iostream>

sf::Clock timer;
sf::Sprite splash;

State_Splash::State_Splash(Game& game) : State(game) {

	Shader shader(std::string("assets/shaders/vertex.vert").c_str(), std::string("assets/shaders/fragment.frag").c_str());
	Shader shadercombo("assets/shaders/combo.shader");
	shader.Activate();

	game.assets.LoadTexture("ArcticSplash", "assets/textures/ArcticSplash.jpg");
	splash = sf::Sprite(game.assets.GetTexture("ArcticSplash"));
	splash.setPosition(0, 0);
	timer.restart();
}

void State_Splash::HandleEvent(sf::Event e) {
	switch (e.type)
	{
	case sf::Event::KeyPressed:
		if (e.key.code == sf::Keyboard::Escape) {
			m_pGame->Shutdown();
		}
	}
}

void State_Splash::HandleInput(GLFWwindow* window) {

}

void State_Splash::Update(double deltaTime) {

	if (timer.getElapsedTime().asSeconds() >= 3) {
		m_pGame->PushState<State_Example>(*m_pGame);
	}
}

void State_Splash::FixedUpdate(double fixedTime) {

}

void State_Splash::Render(GLFWwindow* target) {

	glClearColor(0.0f, 0.4353f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	float positions[6] = {
		-0.5f, -0.5f,
		0.0f,  0.5f,
		0.5f, -0.5f
	};

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	glfwSwapBuffers(target);
}