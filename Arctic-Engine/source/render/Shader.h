#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL\glew.h>
#include <gl\GLU.h>
#include <unordered_map>

class Shader
{
public:
	unsigned int ShaderId;
	Shader(const char* vertPath, const char* fragPath);
	Shader(const std::string& path);

	void Bind() const;
	void Unbind() const;

	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);

private:
	void Compile(std::string vert, std::string frag);
	unsigned int GetUniformLocation(const std::string& name);
	std::unordered_map<std::string, int> m_LocationCashe;
};

struct ShaderSource
{
	std::string VertexSource;
	std::string FragmentSource;
};