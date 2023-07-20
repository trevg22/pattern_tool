cmake_minimum_required(VERSION 3.13)

project(pattern_tool)
set(LANGUAGES C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CXX_STANDARD C++20)
add_executable(prog1 prog1.cpp )
target_include_directories(prog1 PUBLIC imgui imgui/backends)
file(GLOB sources CONFIGURE_DEPENDS "imgui/*.cpp")
 file(GLOB back_sources CONFIGURE_DEPENDS "imgui/backends/*.cpp")
target_sources(prog1 PUBLIC ${sources} imgui/backends/imgui_impl_glfw.cpp imgui/backends/imgui_impl_opengl3.cpp)
add_subdirectory(glfw)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(OpenGL REQUIRED)
target_link_libraries(prog1 glfw OpenGL::GL)

add_executable(prog2 prog2.cpp)



