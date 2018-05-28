#pragma once
#include "../render/Renderer.h"

class Texture
{
private:
	std::string m_filePath;
	std::string m_texName;
	unsigned char * m_data;
	int m_width, m_height, m_bits;
public:
	Texture(const std::string& path);
	Texture();
	~Texture();
	void Bind(unsigned int unit = 0) const;
	void Unbind() const;
	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }
	inline int GetRenderId() const { return m_textureId; }
	unsigned int m_textureId;
};