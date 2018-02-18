#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "..\states\State.h"

class Game
{
public:
	Game();
	virtual ~Game();

	void Run();

	template<typename T, typename... Args>
	void PushState(Args&&... args);
	void PopState();

private:

	State & GetCurrentState();

	sf::RenderWindow m_window;
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