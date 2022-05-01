#include "image.h"
#define STB_IMAGE_IMPLEMENTATION // 한 곳에 구현이 되어있다는 것을 알려주는 -> 없으면 링크 에러 
#include <stb/stb_image.h>


ImageUPtr Image::Load(const std::string& filepath) {
    auto image = ImageUPtr(new Image());
    if (!image->LoadWithStb(filepath))
        return nullptr;
    return std::move(image);
}

    
Image::~Image() {
    if(m_data) {
        stbi_image_free(m_data); // stb_image 내장 함수
    }    
}

bool Image::LoadWithStb(const std::string& filepath) {
    m_data = stbi_load(filepath.c_str(), &m_width, &m_height, &m_channelCount, 0);
    if(!m_data) {
        SPDLOG_ERROR("failed to load image: {}", filepath);
        return false;
    }
    return true;
}
