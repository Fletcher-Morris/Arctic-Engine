#pragma once
#include <string>
#include <iostream>
#include <glfw3.h>
#include <fstream>
#include <sstream>

class Shader
{
public:
	unsigned int ShaderId;
	Shader(const char* vertPath, const char* fragPath);
	void Activate();
	void SetBool(const std::string &name, bool value) const;
	void SetInt(const std::string &name, int value) const;
	void SetFloat(const std::string &name, float value) const;
};