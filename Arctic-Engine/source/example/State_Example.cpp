#include "State_Example.h"
#include "../core/Game.h"
#include "../core/Obj.h"
#include "../render/Shader.h"
#include "../states/State_Splash.h"
#include "../editor/imgui.h"

Obj o;
unsigned int vertBuffer;

State_Example::State_Example(Game& game) : State(game) {

	std::cout << "\nEntered state: (State_Example)" << std::endl;

	if (game.assets.LoadObj("teapot", "assets/models/teapot.obj")) {
		o = game.assets.GetObj("teapot");
	}

	glGenBuffers(1, &vertBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
	glBufferData(GL_ARRAY_BUFFER, o.vertices.size() * sizeof(Vector3), &o.vertices[0], GL_STATIC_DRAW);

	Shader shad("assets/shaders/combo.shader");
	shad.Bind();
}

void State_Example::HandleEvent(sf::Event e) {

}

void State_Example::HandleInput(GLFWwindow* window) {

}

void State_Example::Update(double deltaTime) {

}

void State_Example::FixedUpdate(double fixedTime) {

}

float color[3] = { 0.f, 0.f, 0.f };
void State_Example::GuiUpdate()
{
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
				static bool useDarkMode = true;
				ImGui::MenuItem("Dark Mode", "", &useDarkMode);
				if(useDarkMode) ImGui::StyleColorsDark();
				else ImGui::StyleColorsLight();

				ImGui::Separator();

				if (ImGui::ColorEdit3("Clear Color", color)) {}

				ImGui::EndMenu();
			}
			if (ImGui::MenuItem("Quit", "Alt+F4", false, false)) { m_pGame->~Game(); }
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
		ImGui::Separator();
		ImGui::SameLine(ImGui::GetWindowWidth() - 80);
		ImGui::Text("(%.0f FPS)", ImGui::GetIO().Framerate);
		ImGui::EndMainMenuBar();
	}
}

void State_Example::Render(GLFWwindow* target) {

	//glClearColor(1.0f, 0.4353f, 0.0f, 1.0f);
	glClearColor(color[0], color[1], color[2], 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, o.vertices.size());

	glDisableVertexAttribArray(0);
}