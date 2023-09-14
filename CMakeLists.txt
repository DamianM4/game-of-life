cmake_minimum_required(VERSION 3.16)

project(conway VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(EXECUTABLE_NAME "game_of_life")

find_package(SFML COMPONENTS 
             system window graphics REQUIRED)

set(SOURCES
    src/main.cpp
    src/gol.cpp
    src/graphics.cpp
)

add_executable(${EXECUTABLE_NAME} ${SOURCES})

target_include_directories(${EXECUTABLE_NAME} 
                           PRIVATE
                           "${PROJECT_SOURCE_DIR}")

target_link_libraries(${EXECUTABLE_NAME} sfml-graphics)