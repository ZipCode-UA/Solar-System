cmake_minimum_required(VERSION 3.30.0)
project(SolarSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# TODO - Fetch ImGui
include(FetchContent)

# Fetch ImGui and make availble
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG v1.91.8-docking
)
FetchContent_MakeAvailable(imgui)

# Set ImGui_dir
set(IMGUI_DIR ${CMAKE_BINARY_DIR}/_deps/imgui-src)

# ImGui source files
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# TODO - Find package openGL

# Executable
add_executable(${PROJECT_NAME} "src/SolarSystem.cpp")

# Dirs
add_subdirectory(include)
add_subdirectory(src)
target_link_libraries(${PROJECT_NAME} include)
target_link_libraries(${PROJECT_NAME} src)
