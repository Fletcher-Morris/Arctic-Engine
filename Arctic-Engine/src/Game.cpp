#include "Game.h"

Game::Game() : m_window({1280, 720}, "Arctic Engine")
{

}

Game::~Game()
{

}

void Game::Run()
{

    sf::Clock clock;
    while (m_window.isOpen() && !m_states.empty())
    {
        auto dt = clock.restart();
        auto& state = GetCurrentState();
        state.HandleInput();
        state.Update(dt);
        m_window.clear();
        state.Render(m_window);
        m_window.display();
        HandleEvents();
        TryPop();
    }
}

void Game::TryPop()
{
    if(m_tryPop)
    {
        m_states.pop_back();
    }
}

StateBase& Game::GetCurrentState()
{
    return *m_states.back();
}

void Game::PopState()
{

}

void Game::HandleEvents()
{
    sf::Event e;

    while(m_window.pollEvent(e))
    {
        GetCurrentState().HandleEvent(e);

        switch(e.type)
        {
        case sf::Event::Closed:
            m_window.close();

        default:
            break;
        }
    }
}
