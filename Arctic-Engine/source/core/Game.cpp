#include "Game.h"

Game::Game() : m_window({ 1280, 720 }, "Arctic Engine")
{

}

Game::~Game()
{

}

void Game::Run()
{

	sf::Clock clock;
	constexpr unsigned  TICKS_PER_SECOND = 60;
	const sf::Time      TICKS_PER_UPDATE = sf::seconds(1.0f / float(TICKS_PER_SECOND));
	unsigned    ticks = 0;

	sf::Clock timer;
	auto lastTime = sf::Time::Zero;
	auto lag = sf::Time::Zero;

	while (m_window.isOpen() && !m_states.empty())
	{
		auto& state = GetCurrentState();


		auto time = timer.getElapsedTime();
		auto elapsed = time - lastTime;
		lastTime = time;
		lag += elapsed;

		//  Delta Time
		state.HandleInput();
		state.Update(elapsed);
		//  Fixed Time
		while (lag >= TICKS_PER_UPDATE)
		{
			ticks++;
			lag -= TICKS_PER_UPDATE;
			state.FixedUpdate(elapsed);
		}
		//  Render
		m_window.clear();
		state.Render(m_window);
		m_window.display();
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

void Game::HandleEvents()
{
	sf::Event e;

	while (m_window.pollEvent(e))
	{
		GetCurrentState().HandleEvent(e);

		switch (e.type)
		{
		case sf::Event::Closed:
			m_window.close();

		default:
			break;
		}
	}
}
