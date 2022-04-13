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

*/


void OnFramebufferSizeChange(GLFWwindow* window, int width, int height) {
    SPDLOG_INFO("framebuffer size changed : ({} x {})", width, height);
    glViewport(0,0,width, height); // 그림을 그릴 화면의 위치 및 크기
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
    //glfwInit() 호출 후
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwCreateWindow() 호출 전

    // glfw 윈도우 생성
    SPDLOG_INFO("Create glfw window");
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);
    // auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);
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

    // 아래 PollEvent에서 프레임버퍼사이즈가 바뀐것이 수집되면 On~가 실행되도록 미리 설정
    // 위도우 생성 직후에는 프레임버퍼 변경 이벤트가 발생하지 않으므로 첫 호출은 수동으로 함
    OnFramebufferSizeChange(window, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, OnFramebufferSizeChange);
    glfwSetKeyCallback(window, OnKeyEvent);



    // Main 루프
    SPDLOG_INFO("Start main loop");
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents(); // 키/마우스 이벤트를 수집하는 이벤트!
        glClearColor(0.0f, 0.1f, 0.2f, 0.0f); // 화면을 지울 컬러 // 포문 밖에서 해도됭
        glClear(GL_COLOR_BUFFER_BIT); // 화면을 지우는 것
        // 더블버퍼!
        // front 버퍼와 back 버퍼가 존재하여서
        // 그리는 동안에는 보여주지 않다가 다그려지고 나면 바꿔치기
        // 이를 계속 반복
        glfwSwapBuffers(window);
    }   
    glfwTerminate();
    return 0;
}