#include "State_Example.h"
#include "../core/Game.h"
#include "../render/Shader.h"
#include "../states/State_Splash.h"
#include "../editor/imgui.h"
#include "../core/Texture.h"
#include "../entity/Entity.h"

Mesh o;
Entity e;
unsigned int vertBuffer;
unsigned int uvBuffer;
unsigned int useTexture;
std::string useModel = "spring";
float color[3] = { 0.f, 0.f, 0.f };
bool useDarkMode;
bool editor;

State_Example::State_Example(Game& game) : State(game) {

	std::cout << "\nEntered state: (State_Example)" << std::endl;

	editor = EnginePrefs::Instance()->editor;
	useDarkMode = EnginePrefs::Instance()->guiDark;
	if (useDarkMode) ImGui::StyleColorsDark();
	else ImGui::StyleColorsLight();

	AssetManager::Instance()->LoadMesh("cube", "assets/models/cube.obj");
	AssetManager::Instance()->LoadMesh("teapot", "assets/models/teapot.obj");
	AssetManager::Instance()->LoadMesh("spring", "assets/models/spring.obj");

	AssetManager::Instance()->LoadTexture("splash", "assets/textures/ArcticSplash.jpg");
	AssetManager::Instance()->LoadTexture("hot", "assets/textures/hot.jpg");
	AssetManager::Instance()->LoadTexture("error", "assets/textures/error.png");
	AssetManager::Instance()->LoadTexture("ros", "assets/textures/r.png");
	AssetManager::Instance()->LoadTexture("apt", "assets/textures/apt.jpg");
	AssetManager::Instance()->LoadTexture("blur1", "assets/textures/blur1.jpg");
	AssetManager::Instance()->LoadTexture("blur2", "assets/textures/blur2.jpg");
	AssetManager::Instance()->LoadTexture("blur3", "assets/textures/blur3.jpg");
	AssetManager::Instance()->LoadTexture("blur4", "assets/textures/blur4.jpg");

	o = AssetManager::Instance()->GetMesh(useModel);
	e.SetMesh(&AssetManager::Instance()->GetMesh(useModel));

	//	VERTEX BUFFER
	glGenBuffers(1, &vertBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
	glBufferData(GL_ARRAY_BUFFER, o.vertices.size() * sizeof(Vector3), &o.vertices[0], GL_STATIC_DRAW);

	//	UV BUFFER
	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, o.uvs.size() * sizeof(Vector2), &o.uvs[0], GL_STATIC_DRAW);

	Shader shad("assets/shaders/combo.shader");
	shad.Bind();
}

void State_Example::HandleEvent(int e) {

}

void State_Example::HandleInput(GLFWwindow* window) {

}

void State_Example::Update(double deltaTime) {

}

void State_Example::FixedUpdate(double fixedTime) {

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
						useModel = AssetManager::Instance()->loadedMeshes[i].c_str();
						o = AssetManager::Instance()->GetMesh(useModel);

						//	VERTEX BUFFER
						glGenBuffers(1, &vertBuffer);
						glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
						glBufferData(GL_ARRAY_BUFFER, o.vertices.size() * sizeof(Vector3), &o.vertices[0], GL_STATIC_DRAW);

						//	UV BUFFER
						glGenBuffers(1, &uvBuffer);
						glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
						glBufferData(GL_ARRAY_BUFFER, o.uvs.size() * sizeof(Vector2), &o.uvs[0], GL_STATIC_DRAW);
					}
				}

				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		if(ImGui::Button("Reload Model"))
		{
			AssetManager::Instance()->LoadMesh(useModel, "assets/models/" + useModel + ".obj");
			o = AssetManager::Instance()->GetMesh(useModel);

			//	VERTEX BUFFER
			glGenBuffers(1, &vertBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
			glBufferData(GL_ARRAY_BUFFER, o.vertices.size() * sizeof(Vector3), &o.vertices[0], GL_STATIC_DRAW);

			//	UV BUFFER
			glGenBuffers(1, &uvBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
			glBufferData(GL_ARRAY_BUFFER, o.uvs.size() * sizeof(Vector2), &o.uvs[0], GL_STATIC_DRAW);
		}
		ImGui::Separator();
		ImGui::SameLine(ImGui::GetWindowWidth() - 80);
		ImGui::Text("(%.0f FPS)", ImGui::GetIO().Framerate);
		ImGui::EndMainMenuBar();
	}
}

void State_Example::Render(GLFWwindow* target) {

	glClearColor(color[0], color[1], color[2], 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	VERTEX BUFFER
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//	UV BUFFER
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, o.VertCount);

	AssetManager::Instance()->BindTexture(useTexture);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}