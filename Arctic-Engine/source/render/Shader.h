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
	unsigned int shaderId;
	Shader(const char* _vertPath, const char* _fragPath);
	Shader(const std::string& _comboPath);

	void Bind() const;
	void Unbind() const;

	void SetBool		(const std::string& _name, bool _value) const;
	void SetInt			(const std::string& _name, int _value) const;
	void SetFloat		(const std::string& _name, float _value) const;
	void SetUniform1f	(const std::string& _name, float _value);
	void SetUniform2f(const std::string& _name, float f0, float f1);
	void SetUniform3f(const std::string& _name, float f0, float f1, float f2);
	void SetUniform4f(const std::string& _name, float f0, float f1, float f2, float f3);
	void SetUniform1i	(const std::string& _name, int _value);

private:
	void Compile(std::string _vert, std::string _frag);
	unsigned int GetUniformLocation(const std::string& _name);
	std::unordered_map<std::string, int> m_locations;
};

struct ShaderSource
{
	std::string vertexSource;
	std::string fragmentSource;
};