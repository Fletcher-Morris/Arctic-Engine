#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>
#include <iostream>
#include <GL\glew.h>
#include <glfw3.h>
#include "..\states\State.h"
#include "../states/State_Splash.h"
#include "../render/Shader.h"
#include "../util/AssetManager.h"

class Game
{
public:
	Game();
	virtual ~Game();
	bool Init();
	void Run();

	template<typename T, typename... Args>
	void PushState(Args&&... args);
	void PopState();
	void Shutdown();
	GLFWwindow* window;
	AssetManager assets;

private:

	State & GetCurrentState();
	std::vector<std::unique_ptr<State>>m_states;

	bool m_tryPop = false;
	void HandleEvents();
	void TryPop();
};

template<typename T, typename... Args>
void Game::PushState(Args&&... args)
{
	m_states.push_back(std::make_unique<T>(std::forward<Args>(args)...));
}

#endif // GAME_H