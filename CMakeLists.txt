cmake_minimum_required(VERSION 3.27.8)
project(RoverRun C)

set(CMAKE_C_STANDARD 11)

add_executable(RoverRun main.c
        loc.c
        map.c
        moves.c
        queue.c
        stack.c
        loc.h
        map.h
        moves.h
        queue.h
        stack.h
        Tree.c
        Tree.h
        Node.c
        Node.h
        Robot.c
        Robot.h
)

add_subdirectory(vendors/SDL)
add_subdirectory(vendors/SDL_image)

target_include_directories(${PROJECT_NAME} PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)