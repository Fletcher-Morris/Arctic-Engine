#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "util/Random.h"

int main()
{
    Random<> random;

    for(int i = 0; i < 30; i++){
        std::cout << random.Int(0, 10) << "\n";
    }

    Game game;
    game.Run();

    return 0;
}
