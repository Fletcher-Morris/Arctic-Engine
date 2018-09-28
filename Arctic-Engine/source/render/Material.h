#pragma once

#include "Shader.h"
#include "../util/GlmTypedefs.h"

class Material
{
private:
	Vector3 colour;
	int texture;

public:
	Material() { this->colour = Vector3(0, 0, 0); this->texture = 0; }
	Material(Vector3 _colour, int _texture)
	{
		this->colour = _colour;
		this->texture = _texture;
	}

	~Material() {}

	void ConfigShader(Shader& _shader)
	{
		_shader.SetUniform3f("colour", this->colour);
	}
};