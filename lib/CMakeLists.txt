cmake_minimum_required(VERSION 3.24)

file(GLOB CPP_LIST **/*.cpp)

# Dear IMGUI
set(IMGUI_DIR "../external/imgui-1.89.8")

add_library(enginelib ${CPP_LIST} "${IMGUI_DIR}/imgui.cpp"
    "${IMGUI_DIR}/imgui_demo.cpp"
    "${IMGUI_DIR}/imgui_draw.cpp"
    "${IMGUI_DIR}/imgui_tables.cpp"
    "${IMGUI_DIR}/imgui_widgets.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp")

target_include_directories(enginelib PRIVATE "${IMGUI_DIR}")