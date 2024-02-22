cmake_minimum_required(VERSION 3.16)
project(JetEngine)

FILE(GLOB_RECURSE JetEngineSources src/**.h
                            src/**cpp
                            vendor/stb_image/*.cpp
                            vendor/stb_image/*.h
                            vendor/glm/glm/*.hpp
                            vendor/glm/glm/*inl)

add_library(JetEngine ${JetEngineSources})

include_directories(${CMAKE_SOURCE_DIR}/JetEngine/src
                    ${CMAKE_SOURCE_DIR}/JetEngine/vendor/spdlog/include
                    ${CMAKE_SOURCE_DIR}/JetEngine/vendor/glfw/include
                    ${CMAKE_SOURCE_DIR}/JetEngine/vendor/Glad/include
                    ${CMAKE_SOURCE_DIR}/JetEngine/vendor/imgui
                    ${CMAKE_SOURCE_DIR}/JetEngine/vendor/glm
                    ${CMAKE_SOURCE_DIR}/JetEngine/vendor/stb_image
                    ${OPENGL_INCLUDE_DIR}) # include files from ProjectB

target_precompile_headers(JetEngine PUBLIC src/JEpch.h)

target_link_libraries(JetEngine PUBLIC glfw Glad ImGui ${OPENGL_gl_LIBRARY})


install(TARGETS JetEngine RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin/${CMAKE_PROJECT_NAME})