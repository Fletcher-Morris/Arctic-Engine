#include "Shader.h"

Shader::Shader(const char * vertPath, const char * fragPath)
{
	std::string vertCode;
	std::string fragCode;

	std::ifstream vertFile;
	std::ifstream fragFile;

	vertFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		vertFile.open(vertPath);
		fragFile.open(fragPath);

		std::stringstream vertStream, fragStream;

		vertStream << vertFile.rdbuf();
		fragStream << fragFile.rdbuf();

		vertFile.close();
		fragFile.close();

		vertCode = vertStream.str();
		fragCode = fragStream.str();

		std::cout << "Loaded texture: " + (std::string)vertPath << std::endl;
		std::cout << "Loaded texture: " + (std::string)fragPath << std::endl;
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Failed to load vertex shader: " + (std::string)vertPath << std::endl;
		std::cout << "Failed to load fragment shader: " + (std::string)fragPath << std::endl;
	}

	const char* vertShader = vertCode.c_str();
	const char* fragShader = fragCode.c_str();


	unsigned int vertex, fragment;
	int success;
	char info[512];
	
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertShader, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, info);
		std::cout << "Failed to compile vertex shader:\n" << info << std::endl;
	};

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragShader, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, info);
		std::cout << "Failed to compile fragment shader:\n" << info << std::endl;
	};


	ShaderId = glCreateProgram();
	glAttachShader(ShaderId, vertex);
	glAttachShader(ShaderId, fragment);
	glLinkProgram(ShaderId);

	glGetProgramiv(ShaderId, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ShaderId, 512, NULL, info);
		std::cout << "Failed to link shader:\n" << info << std::endl;
	}


	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::Activate()
{
}

void Shader::SetBool(const std::string & name, bool value) const
{
}

void Shader::SetInt(const std::string & name, int value) const
{
}

void Shader::SetFloat(const std::string & name, float value) const
{
}
