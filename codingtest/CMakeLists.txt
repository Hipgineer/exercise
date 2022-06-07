## Configure
## -- step for preparing build for Visual Studio
# cmake -Bbuild . -DCMAKE_BUILD_TYPE=Debug
cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME BOJ_dbshin)
set(CMAKE_CXX_STANDARD 17)

project(${PROJECT_NAME})
add_executable(${PROJECT_NAME} solving/BOJ10866_deque.cpp)