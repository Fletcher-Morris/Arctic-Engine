#ifndef STATEBASE_H_INCLUDED
#define STATEBASE_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "util/NonCopyable.h"

class Game;

class StateBase : public NonCopyable
{
public:
    StateBase(Game& game):m_pGame(&game){}

    virtual ~StateBase() = default;

    virtual void HandleEvent    (sf::Event e) = 0;
    virtual void HandleInput    () = 0;
    virtual void Update         (sf::Time deltaTime) = 0;
    virtual void FixedUpdate    (sf::Time fixedTime) = 0;
    virtual void Render         (sf::RenderTarget& renderer);

protected:
    Game* m_pGame;
};

#endif // STATEBASE_H_INCLUDED
