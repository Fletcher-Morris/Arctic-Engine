#include "Game.h"

Game::Game() : m_window({1280, 720}, "Arctic Engine")
{

}

Game::~Game()
{

}

void Game::Run()
{
    while (m_window.isOpen() && !m_states.empty()){
        m_window.clear();
        m_window.display();
        HandleEvents();
        if(m_tryPop){
            TryPop();
        }
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
        switch(e.type)
        {
        case sf::Event::Closed:
            m_window.close();

        default:
            break;
        }
    }
}
