## Configure
## 빌드 전 VS형태로 구체화하는 단계
# cmake -Bbuild . -DCMAKE_BUILD_TYPE=Debug

## Build
## 실제 빌드
# cmake --build build --config Debug

cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME opengl_example)
set(CMAKE_CXX_STANDARD 17)

# cpp에서 사용할 것이다.
set(WINDOW_NAME "OpenGL Example")
set(WINDOW_WIDTH 960)
set(WINDOW_HEIGHT 540)

project(${PROJECT_NAME})
add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/common.cpp src/common.h
    src/shader.cpp src/shader.h
    )

include(Dependency.cmake)

# 프로젝트에 include / lib 관련 옵션 추가
# target_include_directories
# 타겟의 이름: add_executable(${PROJECT_NAME} src/main.cpp)
#             spdlog
#             등이 될 수 있다.
target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS}) # 실제로 사용할 라이브러리 .lib은 지워라
target_compile_definitions(${PROJECT_NAME} PUBLIC
    WINDOW_NAME="${WINDOW_NAME}"
    WINDOW_WIDTH=${WINDOW_WIDTH}
    WINDOW_HEIGHT=${WINDOW_HEIGHT}
    )

add_dependencies(${PROJECT_NAME} ${DEP_LIST}) # DEP LIST 컴파일 후에 다하고 나서 PROJECT_NAME을 컴파일해라