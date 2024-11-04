cmake_minimum_required(VERSION 3.5)
project(GooberEngine)

set(CMAKE_CXX_STANDARD 26)

#SDL2 for 2D rendering
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
file(GLOB ASSETS_SRC ${PROJECT_SOURCE_DIR}/root/**/*.*)

add_executable(
        GooberEngine
        engine/Main.cpp
        engine/Goober.cpp
        engine/Goober.h
        ${ASSETS_SRC}
)

target_link_libraries(
        GooberEngine
        ${SDL2_LIBRARIES}
        SDL2_image
        ${Boost_LIBRARIES}
)