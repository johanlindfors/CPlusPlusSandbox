cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(sandbox)

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

file(GLOB SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.c"
)

file(GLOB HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)

file(GLOB SHADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.vs"
    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.fs"
)

foreach(SHADER ${SHADERS})
    file(COPY ${SHADER} DESTINATION ${CMAKE_SOURCE_DIR}/build/)
endforeach(SHADER)

file(GLOB TEXTURES
    "${CMAKE_CURRENT_SOURCE_DIR}/textures/*.png"
)

foreach(TEXTURE ${TEXTURES})
    file(COPY ${TEXTURE} DESTINATION ${CMAKE_SOURCE_DIR}/build/)
endforeach(TEXTURE)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} GLESv2 glfw GL)

set_property(TARGET ${project_name} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${project_name} PROPERTY CXX_STANDARD_REQUIRED ON)
