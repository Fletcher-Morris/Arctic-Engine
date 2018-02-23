#include "Game.h"
#include <iostream>
#include "../states/State_Splash.h"
#include "../render/Shader.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

Game::Game()
{
	
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
	float positions[6] = {
		-0.5f, -0.5f,
		0.0f,  0.5f,
		0.5f, -0.5f
	};

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.0f, 0.5647f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//	RENDER START

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

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