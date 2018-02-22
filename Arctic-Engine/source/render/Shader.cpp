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

		std::cout << "Loaded vertex shader: " + (std::string)vertPath << std::endl;
		std::cout << "Loaded fragment shader: " + (std::string)fragPath << std::endl;
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Failed to load vertex shader: " + (std::string)vertPath << std::endl;
		std::cout << "Failed to load fragment shader: " + (std::string)fragPath << std::endl;
	}

	Parse(vertCode, fragCode);
}

Shader::Shader(std::string vertPath, std::string fragPath)
{
}

Shader::Shader(std::string path)
{
	enum class ShaderType {
		None = -1, Vertex = 0, Fragment = 1
	};

	std::ifstream stream(path);
	std::string line;
	std::stringstream strstr[2];
	ShaderType type = ShaderType::None;
	while (std::getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				std::cout << "Loaded vertex shader: " + (std::string)path << std::endl;
				type = ShaderType::Vertex;
			}
			else if (line.find("fragment") != std::string::npos) {
				std::cout << "Loaded fragment shader: " + (std::string)path << std::endl;
				type = ShaderType::Fragment;
			}
		}
		else {
			strstr[(int)type] << line << "\n";
		}
	}

	Parse(strstr[0].str(), strstr[1].str());
}

void Shader::Activate()
{
	glUseProgram(ShaderId);
}

void Shader::SetBool(const std::string & name, bool value) const
{
	glUniform1i(glGetUniformLocation(ShaderId, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string & name, int value) const
{
	glUniform1i(glGetUniformLocation(ShaderId, name.c_str()), value);
}

void Shader::SetFloat(const std::string & name, float value) const
{
	glUniform1i(glGetUniformLocation(ShaderId, name.c_str()), value);
}

void Shader::Parse(std::string vert, std::string frag)
{
	const char* vertShader = vert.c_str();
	const char* fragShader = frag.c_str();

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
	std::cout << "Linked shader: " << ShaderId << std::endl;


	glDeleteShader(vertex);
	glDeleteShader(fragment);
}
