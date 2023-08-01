cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 17)
project(cengine)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}" include)

add_subdirectory(lib)
target_link_libraries(${PROJECT_NAME} PUBLIC enginelib)

FILE(GLOB LIB_FOLDERS lib/**)
include_directories(${LIB_FOLDERS})
target_include_directories(enginelib PRIVATE "${PROJECT_BINARY_DIR}" ${LIB_FOLDERS})

# External

# GLFW
find_package(GLFW3 REQUIRED)
target_include_directories(enginelib PRIVATE ${GLFW3_INCLUDE_DIR})
target_link_libraries(enginelib PRIVATE ${GLFW3_LIBRARY})

# GLM
set(glm_DIR external/glm/cmake/glm) # if necessary
find_package(glm REQUIRED)
target_link_libraries(enginelib PUBLIC glm::glm)

# GLEW
list(APPEND CMAKE_PREFIX_PATH "D:/GitHub/c-engine/external/glew-2.1.0")
list(APPEND CMAKE_LIBRARY_PATH "D:/GitHub/c-engine/external/glew-2.1.0/lib/Release/Win32/")
find_package(GLEW REQUIRED)
target_link_libraries(enginelib PUBLIC ${GLEW_LIBRARIES})
target_include_directories(enginelib PUBLIC ${GLEW_INCLUDE_DIRS})

# freeglut
set(TESTE_PATH "C:/Program Files (x86)/freeglut/include/")
find_library(FREEGLUT_LIBRARY freeglut "C:/Program Files(x86)/freeglut/lib")
target_link_libraries(enginelib PRIVATE ${FREEGLUT_LIBRARY})
target_include_directories(enginelib PRIVATE ${TESTE_PATH})

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(enginelib PRIVATE ${OPENGL_gl_LIBRARY})

if(NOT OPENGL_FOUND)
    message(ERROR "OPENGL not found!")
endif(NOT OPENGL_FOUND)
