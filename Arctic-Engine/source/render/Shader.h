#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad\glad.h>

class Shader
{
public:
	unsigned int ShaderId;
	Shader(const char* vertPath, const char* fragPath);
	Shader(std::string path);
	void Activate();
	void SetBool(const std::string &name, bool value) const;
	void SetInt(const std::string &name, int value) const;
	void SetFloat(const std::string &name, float value) const;
private:
	void Parse(std::string vert, std::string frag);
};

struct ShaderSource
{
	std::string VertexSource;
	std::string FragmentSource;
};