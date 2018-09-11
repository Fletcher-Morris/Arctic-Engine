#pragma once
#include "../render/Renderer.h"
#include "../stb/stb_image.h"

class Texture
{
private:
	std::string m_filePath;
	std::string m_texName;
	unsigned char * m_data;
	int m_width, m_height, m_bits;
public:
	Texture(const std::string& _path);
	Texture();
	~Texture();
	void Bind(unsigned int _unit = 0) const;
	void Unbind() const;
	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }
	inline int GetRenderId() const { return m_textureId; }
	unsigned int m_textureId;
};