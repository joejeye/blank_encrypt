cmake_minimum_required(VERSION 3.22)

project(blank_encrypt VERSION 1.0
        DESCRIPTION "A simple text file encryption software"
        LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

option(UTF8 "Compile the UTF-8 featured program" ON)

if(UTF8)
    add_executable(blank_encrypt "${CMAKE_SOURCE_DIR}/src/product/utf8_prn.cpp")
else()
    add_executable(blank_encrypt "${CMAKE_SOURCE_DIR}/src/product/ascii_prn.cpp")
endif()

add_subdirectory(lib)
add_subdirectory(src)

target_link_libraries(blank_encrypt BinaryLayer EncodingLayer IOInterface)