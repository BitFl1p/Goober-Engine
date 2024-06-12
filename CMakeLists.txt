cmake_minimum_required(VERSION 3.28)
project(GooberEngine)

set(CMAKE_CXX_STANDARD 26)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
file(GLOB SCRIPTS_SRC ${PROJECT_SOURCE_DIR}/Scripts/*.cpp)

add_executable(GooberEngine
        Engine/Main.cpp
        Engine/Goober.cpp
        Engine/Goober.h
        ${SCRIPTS_SRC})

target_link_libraries(GooberEngine
        ${SDL2_LIBRARIES}
        SDL2_image)