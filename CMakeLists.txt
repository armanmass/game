cmake_minimum_required(VERSION 4.1)
project(DDINVADERS)

list(APPEND CMAKE_PREFIX_PATH "$ENV{HOME}/.local")

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(assets)

