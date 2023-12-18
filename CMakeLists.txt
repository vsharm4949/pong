cmake_minimum_required(VERSION 3.7)

project(Pong)

find_package(SDL2 REQUIRED)

include_directories(SDL2Test ${SDL2_INCLUDE_DIRS})

add_executable(pong.exe src/Main.cpp)
target_link_libraries(pong.exe ${SDL2_LIBRARIES})

