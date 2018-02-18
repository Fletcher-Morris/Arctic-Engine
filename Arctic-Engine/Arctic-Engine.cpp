// Arctic-Engine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "source\core\Game.h"
#include "source\util\Random.h"

int main()
{
	Random<> random;

	for (int i = 0; i < 30; i++) {
		std::cout << random.Int(0, 10) << "\n";
	}

	Game game;
	game.Run();

	return 0;
}
