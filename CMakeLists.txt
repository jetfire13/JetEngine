cmake_minimum_required(VERSION 3.13.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(JetEngine)

add_subdirectory(JetEngine)
add_subdirectory(JetEngine/vendor/Glad)
add_subdirectory(JetEngine/vendor/glfw)
add_subdirectory(JetEngine/vendor/ImGui)
add_subdirectory(SandBox)
