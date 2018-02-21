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
		std::cout << "Failed to load shader: " + (std::string)vertPath << std::endl;
		std::cout << "Failed to load shader: " + (std::string)fragPath << std::endl;
	}

	const char* vertShader = vertCode.c_str();
	const char* fragShader = fragCode.c_str();

	unsigned int vertex, fragment;
	int success;
	char info[512];
}
