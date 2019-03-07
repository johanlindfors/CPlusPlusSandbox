cmake_minimum_required(VERSION 3.0)
project(sandbox)

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

file(GLOB SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
file(GLOB HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})