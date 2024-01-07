cmake_minimum_required(VERSION 3.16)
project(Glad LANGUAGES C)

add_library(Glad include/glad/glad.h
                    include/KHR/khrplatform.h
                    src/glad.c)
include_directories(include) # include files from ProjectB

target_link_libraries(JetEngine PUBLIC glfw Glad ImGui ${OPENGL_gl_LIBRARY})


install(TARGETS Glad RUNTIME DESTINATION /bin/${CMAKE_PROJECT_NAME})