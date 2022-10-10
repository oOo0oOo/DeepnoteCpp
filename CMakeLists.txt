cmake_minimum_required(VERSION 3.24)
project(deepnote)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(deepnote ${SOURCES})
target_link_libraries(deepnote ${CONAN_LIBS})
