#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

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
        sf::RenderWindow m_window;
        bool m_tryPop = false;
};

template<typename T, typename... Args>
void Game::PushState()
{

}

#endif // GAME_H
