cmake_minimum_required(VERSION 3.24)
project(Wavey)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# add_subdirectory(src)

add_executable(Wavey src/main.cpp)
target_link_libraries(Wavey ${CONAN_LIBS})
