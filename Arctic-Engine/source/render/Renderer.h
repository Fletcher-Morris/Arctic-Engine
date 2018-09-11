#pragma once
#include <GL\glew.h>
#include "Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLog(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLog(const char* _function, const char* _file, int _line);