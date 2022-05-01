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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter); // 정수면 i // 작아지면 필터
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter); // 너무 커지면 필터
}

void Texture::SetWrap(uint32_t sWrap, uint32_t tWrap) const {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap); // 영역 밖 x방향
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap); // y방향 영역 밖
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

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, // 4byte가 처리 효율이 좋아서~!
        image->GetWidth(), image->GetHeight(), 0,
        format, GL_UNSIGNED_BYTE, 
        image->GetData());

    glGenerateMipmap(GL_TEXTURE_2D);
}