#include "Shader.h"
#include "Renderer.h"

Shader::Shader()
{
}

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

	Compile(path);
}

void Shader::Compile(const std::string _comboPath)
{
	enum class ShaderType {
		None = -1, Vertex = 0, Fragment = 1
	};

	std::ifstream stream(_comboPath);
	std::string line;
	std::stringstream strstr[2];
	ShaderType type = ShaderType::None;
	while (std::getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				std::cout << "Loaded vertex shader: " + (std::string)_comboPath << std::endl;
				type = ShaderType::Vertex;
			}
			else if (line.find("fragment") != std::string::npos) {
				std::cout << "Loaded fragment shader: " + (std::string)_comboPath << std::endl;
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

void Shader::SetBool(const std::string & _name, bool _value) const
{
	glUniform1i(glGetUniformLocation(shaderId, _name.c_str()), (int)_value);
}

void Shader::SetInt(const std::string & _name, int _value) const
{
	glUniform1i(glGetUniformLocation(shaderId, _name.c_str()), _value);
}

void Shader::SetFloat(const std::string & _name, float _value) const
{
	glUniform1i(glGetUniformLocation(shaderId, _name.c_str()), _value);
}

void Shader::SetUniform1f(const std::string & _name, float _value)
{
	GLCall(glUniform1f(GetUniformLocation(_name), _value));
}

void Shader::SetUniform2f(const std::string & _name, float f0, float f1)
{
	GLCall(glUniform2f(GetUniformLocation(_name), f0, f1));
}

void Shader::SetUniform3f(const std::string & _name, float f0, float f1, float f2)
{
	GLCall(glUniform3f(GetUniformLocation(_name), f0, f1, f2));
}

void Shader::SetUniform4f(const std::string & _name, float f0, float f1, float f2, float f3)
{
	GLCall(glUniform4f(GetUniformLocation(_name), f0, f1, f2, f3));
}

void Shader::SetUniform1i(const std::string & _name, int _value)
{
	GLCall(glUniform1i(GetUniformLocation(_name), _value));
}

void Shader::SetMvpMatrix(const Matrix4 _mvp)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation("u_MVP"), 1, GL_FALSE, glm::value_ptr(_mvp)));
}

void Shader::Compile(std::string _vert, std::string _frag)
{
	const char* vertShader = _vert.c_str();
	const char* fragShader = _frag.c_str();

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

unsigned int Shader::GetUniformLocation(const std::string & _name)
{
	if (m_locations.find(_name) != m_locations.end()) {
		return m_locations[_name];
	}

	GLCall(int location = glGetUniformLocation(shaderId, _name.c_str()));
	if (location == -1) {
		std::cout << "Error: uniform '" << _name << "' does not exist!" << std::endl;
	}
	m_locations[_name] = location;
	return location;
}
