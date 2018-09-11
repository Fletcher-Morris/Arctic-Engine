#include "Shader.h"
#include "Renderer.h"

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

	Compile(vertCode, fragCode);
}

Shader::Shader(const std::string& path)
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

	Compile(strstr[0].str(), strstr[1].str());
}

void Shader::Bind() const
{
	GLCall(glUseProgram(shaderId))
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0))
}

void Shader::SetBool(const std::string & name, bool value) const
{
	glUniform1i(glGetUniformLocation(shaderId, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string & name, int value) const
{
	glUniform1i(glGetUniformLocation(shaderId, name.c_str()), value);
}

void Shader::SetFloat(const std::string & name, float value) const
{
	glUniform1i(glGetUniformLocation(shaderId, name.c_str()), value);
}

void Shader::SetUniform4f(const std::string & name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform1f(const std::string & name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform1i(const std::string & name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::Compile(std::string vert, std::string frag)
{
	const char* vertShader = vert.c_str();
	const char* fragShader = frag.c_str();

	unsigned int vertex, fragment;
	int success;
	char info[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	GLCall(glShaderSource(vertex, 1, &vertShader, NULL));
	GLCall(glCompileShader(vertex));
	GLCall(glGetShaderiv(vertex, GL_COMPILE_STATUS, &success));
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, info);
		std::cout << "Failed to compile vertex shader:\n" << info << std::endl;
	};

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	GLCall(glShaderSource(fragment, 1, &fragShader, NULL));
	GLCall(glCompileShader(fragment));
	GLCall(glGetShaderiv(fragment, GL_COMPILE_STATUS, &success));
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, info);
		std::cout << "Failed to compile fragment shader:\n" << info << std::endl;
	};


	shaderId = glCreateProgram();
	GLCall(glAttachShader(shaderId, vertex));
	GLCall(glAttachShader(shaderId, fragment));
	GLCall(glLinkProgram(shaderId));

	GLCall(glGetProgramiv(shaderId, GL_LINK_STATUS, &success));
	if (!success)
	{
		GLCall(glGetProgramInfoLog(shaderId, 512, NULL, info));
		std::cout << "Failed to link shader:\n" << info << std::endl;
	}
	std::cout << "Linked shader: " << shaderId << std::endl;


	GLCall(glDeleteShader(vertex));
	GLCall(glDeleteShader(fragment));
}

unsigned int Shader::GetUniformLocation(const std::string & name)
{
	if (m_locations.find(name) != m_locations.end()) {
		return m_locations[name];
	}

	GLCall(int location = glGetUniformLocation(shaderId, name.c_str()));
	if (location == -1) {
		std::cout << "Error: uniform '" << name << "' does not exist!" << std::endl;
	}
	m_locations[name] = location;
	return location;
}
