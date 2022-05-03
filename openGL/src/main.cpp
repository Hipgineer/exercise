// #include "common.h"
// #include "shader.h"
// #include "program.h"
#include "context.h"

#include <spdlog/spdlog.h>
#include <glad/glad.h> // GLFW이전에 추가해야함
#include <GLFW/glfw3.h>

/*
OpenGL State setting function
    - State가 opengl context에 저장됨
    - glViewport(), glClearColor()
OpenGL State using function
    - OpenGL Contxext 에 저장된 state를 이용
    - glClear()

Shader : 
    - GPU상에서 실행되는 작은 프로그램
    - GLSL (shading language) C기반 언어
    - Vertex / Fragment
    - Shader 코드는 openGL 코드 내에서 빌드/로딩됨
    - 미리 빌드한 뒤 로딩하는 방법: SPIR-V  
*/


void OnFramebufferSizeChange(GLFWwindow* window, int width, int height) {
    SPDLOG_INFO("framebuffer size changed : ({} x {})", width, height);
    auto context = reinterpret_cast<Context*>(glfwGetWindowUserPointer(window)); // 이렇게 onFramebuffer에서 ㅅ용
    context->Reshape(width, height);
}

void OnCursorPos(GLFWwindow* window, double x, double y) {
    auto context =  reinterpret_cast<Context*>(glfwGetWindowUserPointer(window));
    context->MouseMove(x, y);
}

void OnMouseButton(GLFWwindow* window, int button, int action, int modifier) {
    auto context =  reinterpret_cast<Context*>(glfwGetWindowUserPointer(window));
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    context->MouseButton(button,action, x, y);
}

void OnKeyEvent(GLFWwindow* window,
    int key, int scancode, int action, int mods){
    SPDLOG_INFO("key: {}, scancode: {}, action: {}, modes: {}{}{}",
        key, scancode,
        action == GLFW_PRESS ? "Pressed" :
        action == GLFW_RELEASE ? "Released" :
        action == GLFW_REPEAT ? "Repeat" : "Unknown",
        mods & GLFW_MOD_CONTROL ? "C" : "-",
        mods & GLFW_MOD_SHIFT ? "S" : "-",
        mods & GLFW_MOD_ALT ? "A" : "-");
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

// void Render

int main(int argc, const char** argv)
{
    SPDLOG_INFO("START PROGRAM.");

    // glfw 라이브러리 초기화
    SPDLOG_INFO("Initialize glfw");
    if (!glfwInit()) {
        const char* description = nullptr;
        glfwGetError(&description);
        SPDLOG_ERROR("faied to intialize glfw : {}", description);
        return -1;
    }

    ///OPENGL에 대한 힌트를 주는 부분 glfw함수
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw 윈도우 생성
    SPDLOG_INFO("Create glfw window");
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);
    if(!window){
        SPDLOG_ERROR("faied to create glfw window");
        glfwTerminate();
        return -1;
    }
    
    
    
    // createWindow를 하는 순간 opengl context가 만들어 진다.
    glfwMakeContextCurrent(window);
    // OpenGL context가 만들어진 이후에 glad를 활용해서 OpenGL 함수를 로딩 해야함
    // - gladLoadGLLoader가 opengl을 로딩하는 함수
    // -- 그런데 인자가 함수?
    // -- glfwGetProcAddress:프로세스의 주소를 얻어오는 함수이고 거기에 로드시켣주는 것!
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        SPDLOG_ERROR("failed to initialze gald");
        glfwTerminate();
        return -1;
    }
    // 자, 이제 gl로 시작하는 함수를 사용할 수 있는것
    // 그래서 여기다가 두고 한번 테스트 해보는 듯?
    auto glVersion = glGetString(GL_VERSION); 
    SPDLOG_INFO("OpenGL context version: {}", glVersion);

    // ------ OpenGL을 쓸 수 있는 경계 ------

    // Context 초기화
    auto context = Context::Create();
    if(!context) {
        SPDLOG_ERROR("failed to create context");
        glfwTerminate();
        return -1;
    }
    //viewpot를 바꾸고 싶은데 constext를 사용 못하는 곳에 콜백이 있음
    //그래서 포인터를 사용
    glfwSetWindowUserPointer(window, context.get());
    // auto pointer = (Context*)glfwGetWindowUserPointer(window); // 이렇게 onFramebuffer에서 ㅅ용

    // Create Program : pipe line


    // 아래 PollEvent에서 프레임버퍼사이즈가 바뀐것이 수집되면 On~가 실행되도록 미리 설정
    // 위도우 생성 직후에는 프레임버퍼 변경 이벤트가 발생하지 않으므로 첫 호출은 수동으로 함
    OnFramebufferSizeChange(window, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, OnFramebufferSizeChange);
    glfwSetKeyCallback(window, OnKeyEvent);
    glfwSetCursorPosCallback(window, OnCursorPos);
    glfwSetMouseButtonCallback(window, OnMouseButton);


    // Main 루프
    SPDLOG_INFO("Start main loop");
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents(); // 키/마우스 이벤트를 수집하는 이벤트!
        context->ProcessInput(window);
        context->Render();
        // 더블버퍼!
        // front 버퍼와 back 버퍼가 존재하여서
        // 그리는 동안에는 보여주지 않다가 다그려지고 나면 바꿔치기
        // 이를 계속 반복
        glfwSwapBuffers(window);
    }   
    context.reset(); // 메모리 해제
    //context = nullptr;

    glfwTerminate();
    return 0;
}