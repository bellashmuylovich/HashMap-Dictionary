cmake_minimum_required(VERSION 3.16)
project(HashMap LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(demo
    demo/main.cpp
)

target_include_directories(demo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Optional: show headers in IDE project trees
target_sources(demo PRIVATE
    src/HashMap.hpp
    src/Dictionary.hpp
)
