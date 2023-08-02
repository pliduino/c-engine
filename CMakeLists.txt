cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 17)
project(cengine)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}" include)
add_subdirectory(lib)
target_link_libraries(${PROJECT_NAME} PRIVATE enginelib)

FILE(GLOB LIB_FOLDERS lib/**)
include_directories(${LIB_FOLDERS})
target_include_directories(enginelib PRIVATE "${PROJECT_BINARY_DIR}" ${LIB_FOLDERS})

# External

# GLFW GLM GLEW
list(APPEND CMAKE_PREFIX_PATH "D:/GitHub/c-engine/external/glew-2.1.0")
list(APPEND CMAKE_LIBRARY_PATH "D:/GitHub/c-engine/external/glew-2.1.0/lib/Release/Win32/")
set(FGLUT_PATH "C:/Program Files (x86)/freeglut/include/")
set(GLM_PATH external/glm)

find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)
find_library(FREEGLUT_LIBRARY freeglut "C:/Program Files(x86)/freeglut/lib")
find_package(GLEW REQUIRED)

set(glm_DIR D:/Github/c-engine/external/glm/cmake/glm) # if necessary
find_package(glm REQUIRED)

message(${GLM_INCLUDE_DIRS})

if(NOT OPENGL_FOUND)
    message(ERROR "OPENGL not found!")
endif(NOT OPENGL_FOUND)

target_link_libraries(enginelib PRIVATE glm::glm ${GLFW3_LIBRARY} ${GLEW_LIBRARIES} ${FREEGLUT_LIBRARY} ${OPENGL_gl_LIBRARY})
target_include_directories(enginelib PRIVATE ${GLEW_INCLUDE_DIRS} ${GLFW3_INCLUDE_DIR} ${FGLUT_PATH} ${GLM_INCLUDE_DIRS})
