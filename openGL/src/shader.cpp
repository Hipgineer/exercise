#include "shader.h"

ShaderUPtr Shader::CreateFromFile(const std::string& filename, GLenum shaderType){
    // auto shader = std::uniqueptr<Shader>(new Shader());
    // shader는 이 함수 안에서만 사용되고 나서! 동적할당취소
    // 그런데 밖에서 사용하긴 해야하니까 move로 소유권을 넘겨버림ㄴ
    auto shader = ShaderUPtr(new Shader());
    if (!shader->LoadFile(filename, shaderType))
        return nullptr;
    return std::move(shader);
}

Shader::~Shader() {
    if (m_shader) {
        glDeleteShader(m_shader);
    }
}

bool Shader::LoadFile(const std::string& filename, GLenum shaderType) {
    auto result = LoadTextFile(filename); // in common.h
    if(!result.has_value())
        return false;
    
    // 레퍼런스로 가져와야 메모리 복사가 안일어난다
    auto& code = result.value();
    const char* codePtr = code.c_str();
    int32_t codeLength = (int32_t)code.length();

    // create and compile shader
    m_shader = glCreateShader(shaderType);
    glShaderSource(m_shader, 1, (const GLchar* const*)&codePtr, &codeLength);
    glCompileShader(m_shader);

    int success = 0; 
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success); // iv? integer vector(pointer를 붙여야한다.)
    if (!success){
        char infoLog[1024];
        glGetShaderInfoLog(m_shader, 1024, nullptr, infoLog);
        SPDLOG_ERROR("failed to compile shader: \"{}\"", filename);
        SPDLOG_ERROR("reason: {}", infoLog);
        return false;
    }

    return true;
}