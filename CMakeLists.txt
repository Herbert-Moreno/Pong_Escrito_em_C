cmake_minimum_required(VERSION 3.30)
project(Pong_em_C C)

set(CMAKE_C_STANDARD 23)

set(RAYLIB_VERSION 5.5)
include(FetchContent)
FetchContent_Declare(
        raylib
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
)
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(raylib)

link_libraries(opengl32 gdi32)

add_executable(Pong_em_C main.c)

target_link_libraries(${PROJECT_NAME} raylib)

target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
