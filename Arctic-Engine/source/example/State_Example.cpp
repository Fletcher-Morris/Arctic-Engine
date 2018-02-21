#include "State_Example.h"
#include "../core/Game.h"
#include "../core/Obj.h"
#include "../render/Shader.h"

Obj o;

State_Example::State_Example(Game& game) : State(game) {

	if (game.assets.LoadObj("teapot", "assets/models/teapot.obj")) {
		o = game.assets.GetObj("teapot");
	}
	Shader shader(std::string("assets/shaders/vertex.vert").c_str(), std::string("assets/shaders/fragment.frag").c_str());
}

void State_Example::HandleEvent(sf::Event e) {
	switch (e.type)
	{
	case sf::Event::KeyPressed:
		if (e.key.code == sf::Keyboard::Escape) {
			m_pGame->Shutdown();
		}
	}
}

void State_Example::HandleInput(GLFWwindow* window) {

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void State_Example::Update(double deltaTime) {

}

void State_Example::FixedUpdate(double fixedTime) {

}

void State_Example::Render(GLFWwindow* target) {

	glClearColor(1.0f, 0.4353f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(target);
}