#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include <glad/glad.h>
#include "stb_image.h"

#include <string>
#include <GLFW/glfw3.h>

#include <iostream>


class Texture
{
public:
    Texture();
    ~Texture();
    void LoadFromPath(const std::string& path);
    unsigned int GetTextureID() const { return m_textureID; };
    unsigned int GetWidth() const { return width; };
    unsigned int GetHeight() const { return height; };
    GLenum GetFormat() const { return format; };
    GLenum GetInternalFormat() const { return internalFormat; };
    GLenum GetWrapMode() const { return wrapMode; };
    GLenum GetFilterMode() const { return filterMode; };
    void SetWrapMode(GLenum mode) { wrapMode = mode; glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode); };
    void SetFilterMode(GLenum mode) { filterMode = mode; glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode); };
    GLenum GetInternalFormatAndFormat(int channels, GLenum& internalFormat, GLenum& format);
    void Bind(unsigned int slot = 0);
private:
    unsigned int m_textureID;
    int width;
    int height;
    GLenum format;
    GLenum internalFormat;
    GLenum wrapMode;
    GLenum filterMode;
};


#endif
