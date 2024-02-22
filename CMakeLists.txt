cmake_minimum_required(VERSION 3.13.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

project(JetEngine)

add_subdirectory(JetEngine)
add_subdirectory(JetEngine/vendor/Glad)
add_subdirectory(JetEngine/vendor/glfw)
add_subdirectory(JetEngine/vendor/imgui)
add_subdirectory(SandBox)
