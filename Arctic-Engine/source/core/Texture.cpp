#include "Texture.h"
#include "../stb/stb_image.h"

Texture::Texture(const std::string & path) :m_filePath(path)
{
	GLCall(glGenTextures(1, &m_textureId));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_textureId));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	stbi_set_flip_vertically_on_load(1);
	m_data = stbi_load(path.c_str(), &m_width, &m_height, &m_bits, 4);

	if (m_data) {
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data));
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
		std::cout << "Parsed texture '" << m_filePath << "', ID " << m_textureId << std::endl;
	}
	else
	{
		std::cout << "Failed to parse texture '" << path << "'" << std::endl;
	}

	stbi_image_free(m_data);
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
