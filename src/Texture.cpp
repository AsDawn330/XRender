#define STB_IMAGE_IMPLEMENTATION

#include "Texture.h"



GLenum Texture::GetInternalFormatAndFormat(int channels, GLenum& internalFormat,GLenum& format)
{
    switch (channels)
    {
    case 3:
        internalFormat = GL_RGB8;
        format = GL_RGB;
        break;
    case 4:
        internalFormat = GL_RGBA8;
        format = GL_RGBA;
        break;
    case 1:
        internalFormat = GL_R8;
        format = GL_RED;
        break;
    default:
        internalFormat = GL_RGB8;
        format = GL_RGB;
        break;
    }
}

Texture::Texture()
{
    glGenTextures(1, &m_textureID);

}
Texture::~Texture()
{
    glDeleteTextures(1, &m_textureID);
}

void Texture::LoadFromPath(const std::string& path)
{
    int channels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (data)
    {
        GLenum internalFormat, format;
        GetInternalFormatAndFormat(channels, internalFormat, format);
        glBindTexture(GL_TEXTURE_2D, m_textureID);
        wrapMode = GL_REPEAT;
        filterMode = GL_LINEAR;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
        std::cout << "stb_image error reason: " << stbi_failure_reason() << std::endl;
    }
    
}

void Texture::Bind(unsigned int slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}
