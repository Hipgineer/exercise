#include "context.h"

ContextUPtr Context::Create() {
    auto context = ContextUPtr(new Context());
    if(!context->Init())
        return nullptr;
    return std::move(context);
}

bool Context::Init() {

    // vertex
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };

    // vertextArrayObject는 buffer를 만들기 전에 선언
    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject); // 지금부터 사용할 어레이는 이놈이야!


    // 버퍼를 만든다. 
    glGenBuffers(1, &m_vertexBuffer); 
    // 버퍼에는 버택스의 입자가들어갈 버퍼야 아래에서 추가할꺼니까 이거 보고 있어
    // 위에서 VAO도 바인드 해놧으니까 거기에 같이 바인딩 됨
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); 
    // 불러온버퍼(GL_ARRAY_BUFFER)에 sizeof 만큼의 자리에 vertices(포인터) 를 넣어줘
    // GL_STATIC_DRAW? : 버퍼에 버택스세팅할거고 다신 안바뀔거야.
    // 데이터는 바이트단위로 들어가니까 무슨 정보인지 알려줘야해. ==> VAO
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*9, vertices, GL_STATIC_DRAW);


    // 0 번 AttribArray를 쓸것이다.
    // --> vs의 location의 번호 
    glEnableVertexAttribArray(0);
    // 0 번 AttribArray는 어떻게 생겼냐면 (0)
    // 3개의
    // float데이터고
    // 노말라이즈 할 필요 없고
    // 3개씩 건너 뛰어라 (stride)
    // offset은 0이다.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, 0);

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

    glUseProgram(m_program->Get());
    glDrawArrays(GL_TRIANGLES, 0, 3);
}