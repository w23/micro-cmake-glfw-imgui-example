cmake_minimum_required(VERSION 3.4)

project(cmake-glfw-imgui LANGUAGES CXX)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)

add_library(glad STATIC glad/src/gl.c)
target_include_directories(glad PUBLIC glad/include)
target_link_libraries(glad OpenGL::GL)

add_library(imgui STATIC
	imgui/imgui_demo.cpp
	imgui/imgui_draw.cpp
	imgui/imgui_widgets.cpp
	imgui/imgui_tables.cpp
	imgui/backends/imgui_impl_glfw.cpp
	imgui/backends/imgui_impl_opengl2.cpp
	imgui/imgui.cpp)
target_include_directories(imgui PUBLIC imgui imgui/backends)
target_link_libraries(imgui glfw OpenGL::GL)

add_executable(cmake-glfw-imgui)
target_sources(cmake-glfw-imgui PRIVATE main.cpp glad/src/gl.c)
target_link_libraries(cmake-glfw-imgui glfw glad imgui OpenGL::GL)