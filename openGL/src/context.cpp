#include "context.h"
#include "image.h"

ContextUPtr Context::Create() {
    auto context = ContextUPtr(new Context());
    if(!context->Init())
        return nullptr;
    return std::move(context);
}

bool Context::Init() {

    float vertices[] = {
        
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
        
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.5f, 0.0f, 1.0f,
        
        -0.5f,  0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        
        0.5f,  0.5f, 0.5f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
         0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
         0.5f,  -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f,  -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
         0.5f,  0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f,  0.5f, 0.5f, 0.0f, 0.0f,        
    };

    uint32_t indices[] = {
         0,  2,  1,  2,  0,  3,
         4,  5,  6,  6,  7,  4,
         8,  9, 10, 10, 11,  8,
        12, 14, 13, 14, 12, 15,
        16, 17, 18, 18, 19, 16,
        20, 22, 21, 22, 20, 23,
    };

    m_vertexLayout = VertexLayout::Create();

    m_vertexBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER,GL_STATIC_DRAW, vertices, sizeof(float)*120);

    // vertices가 어떻게 생겼는지 기술해 주는 부분!
    m_vertexLayout->SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*5, 0);
    m_vertexLayout->SetAttrib(2, 2, GL_FLOAT, GL_FALSE, sizeof(float)*5, sizeof(float)*3);
    // m_vertexLayout->SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, 0);


    m_indexBuffer = Buffer::CreateWithData(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices, sizeof(uint32_t)*36);

    ShaderPtr vertShader = Shader::CreateFromFile("./shader/texture.vs", GL_VERTEX_SHADER);
    ShaderPtr fragShader = Shader::CreateFromFile("./shader/texture.fs", GL_FRAGMENT_SHADER);
    if (!vertShader || ! fragShader)
        return false;
    SPDLOG_INFO("vertex shader id {}", vertShader->Get());
    SPDLOG_INFO("fragment shader id {}", fragShader->Get());

    m_program = Program::Create({fragShader, vertShader});
    if(!m_program)
        return false;
    SPDLOG_INFO("program id: {}", m_program->Get());

    // auto loc = glGetUniformLocation(m_program->Get(), "color");
    // m_program->Use(); // 이프로그램으로 그림을 그리겠다.
    // glUniform4f(loc, 1.0f, 1.0f, 0.0f, 1.0f);

    // Initializing
    glClearColor(0.0f, 0.1f, 0.2f, 0.0f); // 화면을 지울 컬러 // 포문 밖에서 해도됭


    // Image load
    auto image = Image::Load("./image/container.jpg");
    if (!image)
        return false ;
    SPDLOG_INFO("image: {}x{}, {} channels",
        image->GetWidth(), image->GetHeight(), image->GetChannelCount());

    // // Create Image
    // auto image = Image::Create(512,512);
    // image->SetCheckImage(16,16);

    m_texture = Texture::CreateFromImage(image.get());

    auto image2 = Image::Load("./image/awesomeface.png");
    if(!image2)
        return false;
    SPDLOG_INFO("image2: {}x{}, {} channels",
        image2->GetWidth(), image2->GetHeight(), image2->GetChannelCount());
    m_texture2= Texture::CreateFromImage(image2.get());
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture->Get());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_texture2->Get());

    m_program->Use();
    m_program->SetUniform("tex", 0);
    m_program->SetUniform("tex2", 1);

    //Model View Projection Transform
    auto model = glm::rotate(glm::mat4(1.0f), glm::radians(-55.0f), glm::vec3(1.0f,0.0f,0.0f));
    auto view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,-3.0f));
    auto proj = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.01f, 10.0f);
    auto transform = proj * view * model;

    m_program->SetUniform("transform", transform); 

    return true;
}

void Context::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    m_program->Use(); 
    auto model = glm::rotate(glm::mat4(1.0f), glm::radians((float)glfwGetTime()*120.0f), glm::vec3(1.0f,0.5f,0.0f));
    
    auto cameraPos = glm::vec3(0.0f,0.0f,10.0f);
    auto cameraTarget = glm::vec3(0.0f,0.0f,0.0f);
    auto cameraUp = glm::vec3(0.0f,1.0f,0.0f);
    // 이거는 항상 쓰기 때문에 이미 함수가 있음
    // auto cameraZ = glm::normalize(cameraPos - cameraTarget);
    // auto cameraX = glm::normalize(glm::cross(cameraUp, cameraZ));
    // auto cameraY = glm::cross(cameraZ, cameraX);
    // auto cameraMat= glm::mat4(
    //     glm::vec4(cameraX, 0.0f),
    //     glm::vec4(cameraY, 0.0f),
    //     glm::vec4(cameraZ, 0.0f),
    //     glm::vec4(cameraPos, 1.0f));
    // auto view = glm::inverse(cameraMat);
    // auto view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,-3.0f));
    auto view = glm::lookAt(cameraPos,cameraTarget,cameraUp);
    auto proj = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.01f, 10.0f);
    auto transform = proj * view * model;
    m_program->SetUniform("transform", transform);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // static float time = 0.0f; 
    // float t = sinf(time) * 0.5f + 0.5f;
    // auto loc = glGetUniformLocation(m_program->Get(), "color");
    // m_program->Use(); 
    // glUniform4f(loc, t*t, 2.0f*t*(1.0f-t), (1.0f-t)*(1.0f-t), 1.0f);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // time += 0.016f;
}
void Context::ProcessInput(GLFWwindow* window) {
    const float cameraSpeed = 0.05f; 
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        m_cameraPos += cameraSpeed * m_cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        m_cameraPos -= cameraSpeed * m_cameraFront;

    auto cameraRight = glm::normalize(glm::cross(m_cameraUp, -m_cameraFront));
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_cameraPos += cameraSpeed * cameraRight;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_cameraPos -= cameraSpeed * cameraRight;
    
}