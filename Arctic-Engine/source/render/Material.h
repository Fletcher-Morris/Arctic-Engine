#pragma once

#include "Shader.h"
#include "../util/GlmTypedefs.h"

class Material
{
private:
	std::string name;
	Shader * shader;
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

	void UpdateShader(Shader& _shader)
	{
		_shader.SetUniform3f("colour", this->colour);
	}

	void SetName(std::string _name) { name = _name; }
	std::string GetName() { return name; }
	void SetShader(Shader * _shader) { shader = _shader; }
	void SetColour(Vector3 _colour) { colour = _colour; }
	void SetTexture(int _texture) { texture = _texture; }
};