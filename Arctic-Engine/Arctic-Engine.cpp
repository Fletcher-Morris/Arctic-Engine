// Arctic-Engine.cpp : Defines the entry point for the console application.
//

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
	game.Run();

	///* Create a windowed mode window and its OpenGL context */
	//GLFWwindow* window;
	//window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	//if (!window)
	//{
	//	glfwTerminate();
	//	return -1;
	//}

	///* Make the window's context current */
	//glfwMakeContextCurrent(window);

	///* Loop until the user closes the window */
	//while (!glfwWindowShouldClose(window))
	//{
	//	/* Render here */
	//	glClear(GL_COLOR_BUFFER_BIT);

	//	glBegin(GL_TRIANGLES);
	//	glVertex2f(-0.5f, -0.5f);
	//	glVertex2f(-0.0f, 0.5f);
	//	glVertex2f(0.5f, -0.5f);
	//	glEnd();

	//	/* Swap front and back buffers */
	//	glfwSwapBuffers(window);

	//	/* Poll for and process events */
	//	glfwPollEvents();
	//}

	//glfwTerminate();

	return 0;
}