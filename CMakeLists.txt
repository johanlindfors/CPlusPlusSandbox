cmake_minimum_required(VERSION 3.0)
project(sandbox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
    
include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

file(GLOB SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp"
)

file(GLOB HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})