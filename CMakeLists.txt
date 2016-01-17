cmake_minimum_required(VERSION 3.4.1 FATAL_ERROR)
project(sdl2cppwrapper)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})

add_library(sdlclass STATIC 
	sdlclass.cpp
	sdlclass.hpp
)

target_include_directories(sdlclass PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
