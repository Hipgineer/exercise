# ExternalProject 관련 명령어 셋 추가
# 새로운 기능을 추가할때 include
# - 즉 ExternalProject_Add를 사용하려고 하는거
include(ExternalProject)

# Dependency 관련 변수 설정
set(DEP_INSTALL_DIR ${PROJECT_BINARY_DIR}/install) # PROJECT_BINARY_DIR : build 폴더 : 미리 지정되어있는 값
set(DEP_INCLUDE_DIR ${DEP_INSTALL_DIR}/include)
set(DEP_LIB_DIR ${DEP_INSTALL_DIR}/lib)

ExternalProject_Add(
    dep-spdlog
    GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
    GIT_TAG "v1.x"
    GIT_SHALLOW 1 # commits 중에 모두 하지말고 가장 최근 것만
    UPDATE_COMMAND "" # 업데이트 할꺼야?
    PATCH_COMMAND "" # 패치 고칠거야?
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR} # -D : definition
    TEST_COMMAND ""
) 
# Dependency 리스트 및 라이브러리 파일 리스트 추가
set(DEP_LIST ${DEP_LIST} dep-spdlog)
set(DEP_LIBS ${DEP_LIBS} spdlog$<$<CONFIG:Debug>:d>) # spdlogd

ExternalProject_Add(
    dep-glfw
    GIT_REPOSITORY "https://github.com/glfw/glfw.git"
    GIT_TAG "3.3.2"
    GIT_SHALLOW 1 # commits 중에 모두 하지말고 가장 최근 것만
    UPDATE_COMMAND "" # 업데이트 할꺼야?
    PATCH_COMMAND "" # 패치 고칠거야?
    CMAKE_ARGS 
        -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR} # -D : definition
        -DGLFW_BUILD_EXAMPLES=OFF # 해당 라이브러리 CMakeList 에서 받아올 수 있다.
        -DGLFW_BUILD_TESTS=OFF
        -DGLFW_BUILD_DOCS=OFF
    TEST_COMMAND ""
) 
set(DEP_LIST ${DEP_LIST} dep-glfw)
set(DEP_LIBS ${DEP_LIBS} glfw3) 

ExternalProject_Add(
    dep-glad
    GIT_REPOSITORY "https://github.com/Dav1dde/glad.git"
    GIT_TAG "v0.1.34"
    GIT_SHALLOW 1 # commits 중에 모두 하지말고 가장 최근 것만
    UPDATE_COMMAND "" # 업데이트 할꺼야?
    PATCH_COMMAND "" # 패치 고칠거야?
    CMAKE_ARGS 
        -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR} # -D : definition
        -DGLAD_INSTALL=ON
    TEST_COMMAND ""
) 
set(DEP_LIST ${DEP_LIST} dep-glad)
set(DEP_LIBS ${DEP_LIBS} glad) 
