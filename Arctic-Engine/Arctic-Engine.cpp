 /*Arctic-Engine.cpp : Defines the entry point for the console application.*/


#include "stdafx.h"
#include <iostream>
#include "source\core\Game.h"
#include "source\util\Random.h"
#include <glfw3.h>

int main()
{
	Random<> random;
	
	if (!glfwInit())
		return -1;

	Game game;

	return 0;
}