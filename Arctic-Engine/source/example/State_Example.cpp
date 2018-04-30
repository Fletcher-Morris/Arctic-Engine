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

	//shad = Shader("assets/shaders/vertex.vert", "assets/shaders/fragment.frag");

	glGenBuffers(1, &vertBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
	glBufferData(GL_ARRAY_BUFFER, o.vertices.size() * sizeof(Vector3), &o.vertices[0], GL_STATIC_DRAW);
}

void State_Example::HandleEvent(sf::Event e) {

}

void State_Example::HandleInput(GLFWwindow* window) {

}

void State_Example::Update(double deltaTime) {

}

void State_Example::FixedUpdate(double fixedTime) {

}

void State_Example::GuiUpdate()
{
	ImGui::Text("Arctic Engine GUI");
	ImGui::Text("(%.0f FPS)", ImGui::GetIO().Framerate);

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New Scene")) {}
			if (ImGui::MenuItem("Open Scene", "Ctrl+O")) {}
			if (ImGui::MenuItem("Save Scene", "Ctrl+S")) {}
			if (ImGui::MenuItem("Save As...")) {}
			ImGui::Separator();
			if (ImGui::BeginMenu("Options"))
			{
				static bool useDarkMode = true;
				ImGui::MenuItem("Dark Mode", "", &useDarkMode);
				if(useDarkMode) ImGui::StyleColorsDark();
				else ImGui::StyleColorsLight();

				ImGui::EndMenu();
			}
			if (ImGui::MenuItem("Quit", "Alt+F4")) { m_pGame->~Game(); }
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void State_Example::Render(GLFWwindow* target) {

	glClearColor(1.0f, 0.4353f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//shad.Activate();

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, o.vertices.size());

	glDisableVertexAttribArray(0);
}