#include "context.h"

ContextUPtr Context::Create() {
    auto context = ContextUPtr(new Context());
    if(!context->Init())
        return nullptr;
    return std::move(context);
}

bool Context::Init() {

    float vertices[] = {
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
    };

    uint32_t indices[] = {
        0, 1, 3,
        1, 2, 3,
    };

    // vertextArrayObject는 buffer를 만들기 전에 선언
    m_vertexLayout = VertexLayout::Create();
    // glGenVertexArrays(1, &m_vertexArrayObject);
    // glBindVertexArray(m_vertexArrayObject); // 지금부터 사용할 어레이는 이놈이야!

    m_vertexBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER,GL_STATIC_DRAW, vertices, sizeof(float)*12);

    m_vertexLayout->SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, 0);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, 0);

    m_indexBuffer = Buffer::CreateWithData(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices, sizeof(uint32_t)*6);

    ShaderPtr vertShader = Shader::CreateFromFile("./shader/simple.vs", GL_VERTEX_SHADER);
    ShaderPtr fragShader = Shader::CreateFromFile("./shader/simple.fs", GL_FRAGMENT_SHADER);
    if (!vertShader || ! fragShader)
        return false;
    SPDLOG_INFO("vertex shader id {}", vertShader->Get());
    SPDLOG_INFO("fragment shader id {}", fragShader->Get());

    m_program = Program::Create({fragShader, vertShader});
    if(!m_program)
        return false;
    SPDLOG_INFO("program id: {}", m_program->Get());

    auto loc = glGetUniformLocation(m_program->Get(), "color");
    m_program->Use(); // 이프로그램으로 그림을 그리겠다.
    glUniform4f(loc, 1.0f, 1.0f, 0.0f, 1.0f);

    // Initializing
    glClearColor(0.0f, 0.1f, 0.2f, 0.0f); // 화면을 지울 컬러 // 포문 밖에서 해도됭

    return true;
}

void Context::Render() {
    glClear(GL_COLOR_BUFFER_BIT);

    static float time = 0.0f; 
    float t = sinf(time) * 0.5f + 0.5f;
    auto loc = glGetUniformLocation(m_program->Get(), "color");
    m_program->Use(); 
    glUniform4f(loc, t*t, 2.0f*t*(1.0f-t), (1.0f-t)*(1.0f-t), 1.0f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    time += 0.016f;
}