#include "State_Splash.h"
#include "../core/Game.h"
#include "../example/State_Example.h"
#include <iostream>

float positions[6] = {
	-0.5f, -0.5f,
	0.0f,  0.5f,
	0.5f, -0.5f
};

unsigned int buffer;

State_Splash::State_Splash(Game& game) : State(game) {

	//std::cout << "Initialised state system" << std::endl;
}

void State_Splash::HandleEvent(int e) {
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

void State_Splash::GuiUpdate()
{
}

void State_Splash::Render(GLFWwindow* target) {

	m_pGame->PushState<State_Example>(*m_pGame);

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	glClearColor(0.0f, 0.5647f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}