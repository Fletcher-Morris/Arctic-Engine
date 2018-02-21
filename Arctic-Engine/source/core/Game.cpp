#include "Game.h"
#include <iostream>
#include "../states/State_Splash.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

Game::Game()
{
	std::cout << "Initialised OpenGL 4.6" << std::endl;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	PushState<State_Splash>(*this);

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	window = glfwCreateWindow(mode->width/2, mode->height/2, "Arctic Engine", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	std::cout << "Creating OpenGL context (" << mode->width/2 << " x " << mode->height/2 << ")" << std::endl;
	glViewport(0, 0, mode->width, mode->height);

	assets.LoadImage("icon", "assets/textures/icon.jpg");
}

Game::~Game()
{

}

void Game::Run()
{
	if (!window)
	{
		glfwTerminate();
	}

	constexpr unsigned  TICKS_PER_SECOND = 60;
	double lastTime = 0.0;

	while (!glfwWindowShouldClose(window) && !m_states.empty())
	{
		auto& state = GetCurrentState();


		double time = glfwGetTime();
		double dt = time - lastTime;
		lastTime = time;

		//  Delta Time
		state.HandleInput(window);
		state.Update(dt);
		//  Render
		state.Render(window);
		glfwPollEvents();
		//  Events
		HandleEvents();
		TryPop();
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

const GLFWwindow* Game::GetWindow() const
{
	return window;
}

void Game::HandleEvents()
{
	/*sf::Event e;

	while (m_window.pollEvent(e))
	{
		GetCurrentState().HandleEvent(e);

		switch (e.type)
		{
		case sf::Event::Closed:
			Shutdown();

		default:
			break;
		}
	}*/
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}