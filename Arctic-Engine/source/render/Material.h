#pragma once

#include "Shader.h"
#include "../util/GlmTypedefs.h"

class Material
{
private:
	Vector3 colour;
	int texture;

public:
	Material(Vector3 _colour, int _texture)
	{
		this->colour = _colour;
		this->texture = _texture;
	}

	~Material() {}

	void ConfigShader(Shader& _shader)
	{

	}
};