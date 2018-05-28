#include "Texture.h"

Texture::Texture(const std::string & path)
	: m_textureId(0), m_filePath(path), m_data(nullptr), m_width(0), m_height(0), m_bits(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_data = stbi_load(path.c_str(), &m_width, &m_height, &m_bits, 4);


	GLCall(glGenTextures(1, &m_textureId));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_textureId));
	std::cout << "Generated texture to " << m_textureId << std::endl;

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	if (m_data) {
		GLCall(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data));
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
		stbi_image_free(m_data);
	}
	else
	{
		std::cout << "Failed to parse texture '" << path << "'" << std::endl;
	}
}

Texture::Texture()
{

}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_textureId));
}

void Texture::Bind(unsigned int unit) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + unit));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_textureId));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
