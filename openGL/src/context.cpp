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

    // Initializing
    glClearColor(0.0f, 0.1f, 0.2f, 0.0f); // 화면을 지울 컬러 // 포문 밖에서 해도됭

    return true;
}

void Context::Render() {
    glClear(GL_COLOR_BUFFER_BIT);

    m_program->Use();
    // 지금 바인딩 되어있는 VAO의 VBO로 그림
    // 몇번째부터 그릴건지, 몇 개의 데이터를 그릴건지
    // glDrawArrays(GL_TRIANGLES, 0, 6); 
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}