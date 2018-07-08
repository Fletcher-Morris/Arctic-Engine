#include "Game.h"
#include "../editor/imgui.h"
#include "../editor/imgui_impl_glfw_gl3.h"
#include "../render/VertexArray.h"
#include "../render/VertexBufferLayout.h"
#include "../render/IndexBuffer.h"
#include "Texture.h"
#include "../util/ConsoleColour.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

Game::Game()
{
	if (!Init()) {
		Shutdown();
	}

	Run();
}

Game::~Game()
{
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
}

bool Game::Init()
{
	std::cout << "===============================================" << std::endl;
	std::cout << "Initialising Arctic Engine " << ENGINE_CONFIG << std::endl;
	std::cout << "===============================================" << std::endl;
	//	GLFW
	if (!glfwInit()) {
		std::cout << red << "Failed to initialise GLFW!" << std::endl;
		return false;
	}
	std::cout << "Initialised GLFW (" << glfwGetVersionString() << ")" << std::endl;
	glfwWindowHint(GLFW_SAMPLES, 4);
	glEnable(GL_MULTISAMPLE);
	window = glfwCreateWindow(960, 540, "Arctic Engine", NULL, NULL);
	if (!window) {
		std::cout << red << "Failed to create GLFW window!" << std::endl;
	}
	PushState<State_Splash>(*this);
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	//	GLEW
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << red << "Failed to initialise GLEW!" << std::endl;
		return false;
	}
	std::cout << "Initialised GLEW (" << glewGetString(GLEW_VERSION) << ")" << std::endl;
	std::cout << "Initialised OpenGL (" << glGetString(GL_VERSION) << ")" << std::endl;

	//	ImGui
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();
	std::cout << "Initialised ImGui (" << ImGui::GetVersion() << ")" << std::endl;

	std::cout << "===============================================" << std::endl;



	//EnginePrefs::Instance

	return true;
}

void Game::Run()
{
	float positions[] =
	{
		-1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, -1.f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 1.0f
	};

	unsigned int indeces[] =
	{
		0,1,2,
		2,3,0
	};

	VertexArray va;
	VertexBuffer vb(positions, 4 * 4 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	IndexBuffer ib(indeces, 6);

	Shader shad("assets/shaders/combo.shader");
	shad.Bind();
	shad.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

	shad.SetUniform1i("u_Texture", 0);

	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shad.Unbind();

	Renderer rend;


	//	Delta Time Stuff
	double currentFrameTime = glfwGetTime();
	double lastFrameTime = currentFrameTime;
	double deltaTime = currentFrameTime = lastFrameTime;

	while (!glfwWindowShouldClose(window) && !m_states.empty())
	{
		currentFrameTime = glfwGetTime();
		deltaTime = currentFrameTime = lastFrameTime;
		lastFrameTime = currentFrameTime;

		glfwPollEvents();
		ImGui_ImplGlfwGL3_NewFrame();

		GetCurrentState().Update(deltaTime);

		//	RENDER START

		GetCurrentState().Render(window);

		rend.Draw(va, ib, shad);

		//	RENDER END

		GetCurrentState().GuiUpdate();
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

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

void window_close_callback(GLFWwindow* window)
{
	glfwSetWindowShouldClose(window, true);
}