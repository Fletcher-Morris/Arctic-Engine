#pragma once
#include "../render/Renderer.h"

class Texture
{
private:
	unsigned int m_rendererId;
	std::string m_filePath;
	unsigned char* m_buffer;
	int m_width, m_height, m_bits;
public:
	Texture(const std::string& path);
	~Texture();
	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }
};