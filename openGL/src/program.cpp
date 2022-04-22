#include "program.h"

Program::~Program() {
    if(m_program)
    {
        glDeleteProgram(m_program);
    }        
}

ProgramUPtr Program::Create(const std::vector<ShaderPtr>& shaders) {
    auto program = ProgramUPtr(new Program());
    if (!program->Link(shaders))
        return nullptr;
    return std::move(program);
}

bool Program::Link(const std::vector<ShaderPtr>& shaders){
    m_program = glCreateProgram(); // id를 얻는다
    for (auto& shader:shaders) // c++11
        glAttachShader(m_program, shader->Get()); // 인자 shader id 를 가져온다.

    glLinkProgram(m_program);
    int success = 0;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetProgramInfoLog(m_program, 1024, nullptr, infoLog);
        SPDLOG_ERROR("faailed to link program: {}", infoLog);
        return false;
    }
    return true;
}


void Program::Use() const {
    glUseProgram(m_program);
}