cmake_minimum_required(VERSION 3.24)

file(GLOB CPP_LIST **/*.cpp)

add_library(enginelib ${CPP_LIST})

# External
# target_link_libraries(${PROJECT_NAME} PUBLIC GLFW)