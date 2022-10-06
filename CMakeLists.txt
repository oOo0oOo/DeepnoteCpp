cmake_minimum_required(VERSION 3.24.2)
project(Wavey)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(wavey src/main.cpp)
target_link_libraries(wavey ${CONAN_LIBS})
