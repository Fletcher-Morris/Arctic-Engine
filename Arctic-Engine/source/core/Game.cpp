#include "Game.h"
#include <iostream>
#include "../states/State_Splash.h"
#include "../render/Shader.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

Game::Game()
{
	PushState<State_Splash>(*this);

	if (!Init()) {
		glfwTerminate();
	}

	Run();
}

Game::~Game()
{
	glfwTerminate();
}

bool Game::Init()
{
	if (!glfwInit()) {
		std::cout << "Failed to initialise GLFW!" << std::endl;
		return false;
	}
	std::cout << "Initialised GLFW (" << glfwGetVersionString() << ")" << std::endl;
	window = glfwCreateWindow(960, 540, "Arctic Engine", NULL, NULL);
	if (!window) {
		std::cout << "Failed to create GLFW window!" << std::endl;
	}
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD!" << std::endl;
		return false;
	}
	std::cout << "Initialised GLAD" << std::endl;
	std::cout << "Initialised OpenGL (" << glGetString(GL_VERSION) << ")\n" << std::endl;

	return true;


}

void Game::Run()
{
	while (!glfwWindowShouldClose(window) && !m_states.empty())
	{
		glfwPollEvents();

		//	RENDER START

		GetCurrentState().Render(window);

		//	RENDER END

		glfwSwapBuffers(window);
	}
}

void Game::TryPop()
{
	if (m_tryPop)
	{
		m_states.pop_back();
	}
}

State& Game::GetCurrentState()
{
	return *m_states.back();
}

void Game::PopState()
{

}

void Game::Shutdown()
{
	glfwDestroyWindow(window);
}

void Game::HandleEvents()
{

}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}