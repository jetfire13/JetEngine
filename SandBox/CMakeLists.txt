cmake_minimum_required(VERSION 3.9)
project(SandBox)

FILE(GLOB SandBoxSources src/*.h src/*.cpp)

add_executable(SandBox ${SandBoxSources})
include_directories(${CMAKE_SOURCE_DIR}/JetEngine/vendor/spdlog/include
                    ${CMAKE_SOURCE_DIR}/JetEngine/src
                    ${CMAKE_SOURCE_DIR}/JetEngine/vendor
                    ${CMAKE_SOURCE_DIR}/JetEngine/vendor/glm) # include files from ProjectB
target_link_libraries(SandBox PUBLIC JetEngine) 

install(TARGETS SandBox RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin/${CMAKE_PROJECT_NAME})