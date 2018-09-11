#include "Renderer.h"
#include "../util/ConsoleColour.h"
#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLog(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << red << "[OpenGl Error] (" << error << "): " << function << " " << file << ":" << line << white << std::endl;
		return false;
	}
	return true;
}