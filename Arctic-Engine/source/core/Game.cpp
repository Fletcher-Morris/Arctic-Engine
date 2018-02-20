#include "Game.h"
#include <iostream>
#include "../states/State_Splash.h"

Game::Game() : m_window({ sf::VideoMode::getDesktopMode().width/2, sf::VideoMode::getDesktopMode().height / 2 }, "Arctic Engine")
{
	std::cout << "Initialised OpenGL 4.6" << std::endl;
	std::cout << "Creating OpenGL context (" << m_window.getSize().x << " x " << m_window.getSize().y << ")" << std::endl;
	assets.LoadImage("icon", "assets/textures/icon.jpg");
	m_window.setIcon(128,128,assets.GetImage("icon").getPixelsPtr());
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

	PushState<State_Splash>(*this);

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

void Game::Shutdown()
{
	m_window.close();
}

const sf::RenderWindow& Game::GetWindow() const
{
	return m_window;
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
			Shutdown();

		default:
			break;
		}
	}
}

