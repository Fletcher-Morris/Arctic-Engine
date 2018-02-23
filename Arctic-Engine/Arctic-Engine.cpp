 /*Arctic-Engine.cpp : Defines the entry point for the console application.*/


#include "stdafx.h"
#include <iostream>
#include "source\core\Game.h"
#include "source\util\Random.h"
#include <glfw3.h>

int main()
{
	Random<> random;
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Game game;

	return 0;
}