cmake_minimum_required(VERSION 2.8.4)
project(AlgebraEngineEmscripten)

ADD_DEFINITIONS(
    -std=c++11
)

#set(PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/cpp/")
#set(CMAKE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/cpp/")
add_subdirectory("${PROJECT_SOURCE_DIR}/cpp/")

add_executable(AEEXEC ./cpp/main.cpp)
TARGET_LINK_LIBRARIES(AEEXEC AlgebraEngine)

