#include "State_Example.h"
#include "../core/Game.h"
#include "../render/Shader.h"
#include "../states/State_Splash.h"
#include "../editor/imgui.h"
#include "../core/Texture.h"
#include "../entity/Entity.h"

unsigned int useTexture;
float color[3] = { 0.f, 0.5f, 1.0f };
bool useDarkMode;
bool editor;
int renderMethod = 0;

State_Example::State_Example(Game& game) : State(game) {

	std::cout << "\nEntered state: (State_Example)" << std::endl;

	editor = EnginePrefs::Instance()->editor;
	useDarkMode = EnginePrefs::Instance()->guiDark;
	if (useDarkMode) ImGui::StyleColorsDark();
	else ImGui::StyleColorsLight();

	ImGui::GetFont()->Scale = EnginePrefs::Instance()->guiScale;

	Shader shad("assets/shaders/combo.shader");
	shad.Bind();

	AssetManager::Instance()->LoadMesh("quad", "assets/models/quad.obj");
	AssetManager::Instance()->LoadMesh("cube", "assets/models/cube.obj");
	AssetManager::Instance()->LoadMesh("sphere", "assets/models/sphere.obj");
	AssetManager::Instance()->LoadMesh("spring", "assets/models/spring.obj");
	AssetManager::Instance()->LoadMesh("teapot", "assets/models/teapot.obj");
	AssetManager::Instance()->LoadMesh("dragon", "assets/models/dragonsmall.obj");

	AssetManager::Instance()->LoadTexture("splash", "assets/textures/ArcticSplash.jpg");
	AssetManager::Instance()->LoadTexture("hot", "assets/textures/hot.jpg");
	AssetManager::Instance()->LoadTexture("error", "assets/textures/error.png");
	AssetManager::Instance()->LoadTexture("ros", "assets/textures/r.png");
	AssetManager::Instance()->LoadTexture("apt", "assets/textures/apt.jpg");
	AssetManager::Instance()->LoadTexture("blur1", "assets/textures/blur1.jpg");
	AssetManager::Instance()->LoadTexture("blur2", "assets/textures/blur2.jpg");
	AssetManager::Instance()->LoadTexture("blur3", "assets/textures/blur3.jpg");
	AssetManager::Instance()->LoadTexture("blur4", "assets/textures/blur4.jpg");


	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	currentScene.NewEntity("CamObject");
	currentScene.entities[0].AttachComponent<Camera>();
	currentScene.entities[0].GetComponent<Camera>()->DoAThing();
	currentScene.entities[0].AttachComponent<Camera>();
}

void State_Example::HandleEvent(int e) {

}

void State_Example::HandleInput(GLFWwindow* window) {

}

void State_Example::Update(double deltaTime) {

	//	FOR EACH ENTITY IN SCENE
	for (int i = 0; i < currentScene.entityCount; i++)
	{
		currentScene.entities[i].Update(deltaTime);
	}
}

void State_Example::FixedUpdate(double fixedTime) {

	//	FOR EACH ENTITY IN SCENE
	for (int i = 0; i < currentScene.entityCount; i++)
	{
		currentScene.entities[i].FixedUpdate(fixedTime);
	}
}

void State_Example::GuiUpdate()
{
	if (!editor) return;

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New Scene","Ctrl+N", false, false)) {}
			if (ImGui::MenuItem("Open Scene", "Ctrl+O", false, false)) {}
			if (ImGui::MenuItem("Save Scene", "Ctrl+S", false, false)) {}
			if (ImGui::MenuItem("Save As...","", false, false)) {}
			ImGui::Separator();
			if (ImGui::BeginMenu("Options"))
			{
				ImGui::MenuItem("Dark Mode", "", &useDarkMode);
				if(useDarkMode) ImGui::StyleColorsDark();
				else ImGui::StyleColorsLight();

				ImGui::Separator();

				if (ImGui::ColorEdit3("Clear Color", color)) {}

				ImGui::EndMenu();
			}
			if (ImGui::MenuItem("Quit", "Alt+F4", false, true)) { m_pGame->~Game(); }
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X", false, false)) {}
			if (ImGui::MenuItem("Copy", "CTRL+C", false, false)) {}
			if (ImGui::MenuItem("Paste", "CTRL+V", false, false)) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Scene"))
		{
			if (ImGui::MenuItem("New Cube", "CTRL+N")) { currentScene.NewEntity("cube"); }
			if (ImGui::MenuItem("New Teapot", "CTRL+N")) { currentScene.NewEntity("teapot"); }
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Assets"))
		{
			if (ImGui::BeginMenu("Textures"))
			{
				for (int i = 1; i < AssetManager::Instance()->GetLoadedTextureCount() + 2; i++)
				{
					GLCall(glBindTexture(GL_TEXTURE_2D, i));
					if (ImGui::ImageButton((GLuint*)i, ImVec2(50.0f, 50.0f), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128))) { useTexture = i; }
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Models"))
			{
				for (int i = 0; i < AssetManager::Instance()->loadedMeshes.size(); i++)
				{
					if (ImGui::Button(AssetManager::Instance()->loadedMeshes[i].c_str()))
					{

					}
				}

				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		if(ImGui::Button("Reload Model"))
		{

		}

		ImGui::Separator();
		ImGui::SameLine(ImGui::GetWindowWidth() - (80 * EnginePrefs::Instance()->guiScale));
		ImGui::Text("(%.0f FPS)", ImGui::GetIO().Framerate);
		ImGui::EndMainMenuBar();
	}

	if (ImGui::Button("QUAD"))
	{
		currentScene.ClearEntities();
		currentScene.NewEntity("quad", "quad");
	}
	if (ImGui::Button("CUBE"))
	{
		currentScene.ClearEntities();
		currentScene.NewEntity("cube", "cube");
	}
	if (ImGui::Button("SPHERE"))
	{
		currentScene.ClearEntities();
		currentScene.NewEntity("sphere", "sphere");
	}
	if (ImGui::Button("SPRING"))
	{
		currentScene.ClearEntities();
		currentScene.NewEntity("spring", "spring");
	}
	if (ImGui::Button("TEAPOT"))
	{
		currentScene.ClearEntities();
		currentScene.NewEntity("teapot", "teapot");
	}
	if (ImGui::Button("DRAGON"))
	{
		currentScene.ClearEntities();
		currentScene.NewEntity("dragon", "dragon");
	}
	

	if (ImGui::Button("FACES"))
	{
		renderMethod = 0;
	}
	if (ImGui::Button("LINES"))
	{
		renderMethod = 1;
	}
	if (ImGui::Button("POINTS"))
	{
		renderMethod = 2;
	}
}

void State_Example::Render(GLFWwindow* target) {

	glClearColor(color[0], color[1], color[2], 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//	FOR EACH ENTITY IN SCENE
	for (int i = 0; i < currentScene.entityCount; i++)
	{
		currentScene.entities[i].Render(renderMethod);
	}

	AssetManager::Instance()->BindTexture(useTexture);
}