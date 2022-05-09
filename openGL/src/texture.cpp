#include "texture.h"

TextureUPtr Texture::CreateFromImage(const Image* image) {
    auto texture = TextureUPtr(new Texture());
    texture->CreateTexture();
    texture->SetTextureFromImage(image);
    return std::move(texture);
}

Texture::~Texture() {
    if (m_texture) {
        glDeleteTextures(1, &m_texture);
    }
}

void Texture::Bind() const {
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Texture::SetFilter(uint32_t minFilter, uint32_t magFilter) const {    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter); // filter for minimally zooming out
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter); // filter for maximally zooming in
}

void Texture::SetWrap(uint32_t sWrap, uint32_t tWrap) const {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap); // filter for pixels outside of x-dir boundary
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap); // filter for pixels outside of y-dir boundary
}

void Texture::CreateTexture() {
    glGenTextures(1, &m_texture);
    // Bind and Set default filter and wrap option
    Bind();
    SetFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    SetWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
}

void Texture::SetTextureFromImage(const Image* image) {
    GLenum format = GL_RGBA;
    switch(image->GetChannelCount()) {
        default: break;
        case 1: format = GL_RED; break;
        case 2: format = GL_RG; break;
        case 3: format = GL_RGB; break;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, // RGBA? ==> 4bytes : efficient
        image->GetWidth(), image->GetHeight(), 0,
        format, GL_UNSIGNED_BYTE, 
        image->GetData());

    glGenerateMipmap(GL_TEXTURE_2D);
}