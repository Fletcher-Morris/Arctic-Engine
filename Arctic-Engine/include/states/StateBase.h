#ifndef STATEBASE_H_INCLUDED
#define STATEBASE_H_INCLUDED
#include <SFML/Graphics.hpp>

class StateBase
{
public:
    StateBase(Game& game):m_pGame(&game){}

    virtual void HandleEvent    (sf::Event e) = 0;
    virtual void HandleInput    () = 0;
    virtual void Update         (sf::Time dt) = 0;
    virtual void Render         (sf::RenderTarget& renderer);
};

#endif // STATEBASE_H_INCLUDED
