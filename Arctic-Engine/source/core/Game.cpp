#include "Game.h"
#include <iostream>
#include "../states/State_Splash.h"
#include "../render/Shader.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

Game::Game()
{
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
		glfwTerminate();
	}

	std::cout << "Initialised OpenGL (" << glGetString(GL_VERSION) << ")" << std::endl;
	std::cout << "Initialised GLFW (" << glfwGetVersionString() << ")" << std::endl;

	std::cout << "Creating OpenGL context (" << mode->width/2 << " x " << mode->height/2 << ")" << std::endl;
	glViewport(0, 0, mode->width, mode->height);

	assets.LoadImage("icon", "assets/textures/icon.jpg");

	PushState<State_Splash>(*this);

	Run();
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