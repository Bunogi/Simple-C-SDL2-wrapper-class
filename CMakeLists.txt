cmake_minimum_required(VERSION 3.4.1 FATAL_ERROR)

option(USE_CLANG "Use Clang for compilation instead of whatever you have by default" OFF)

if(USE_CLANG)
	message("Compiling with Clang")
	set(CMAKE_CXX_COMPILER "clang++")
endif()

project(sdl2cppwrapper)

option(TTF_SUPPORT "Support for printing things to the screen, requires SDL_TTF" OFF)

if(TTF_SUPPORT)
	message("Enabling TTF Support")
	add_definitions(-DTTF_SUPPORT)
	include(FindPkgConfig)
	pkg_search_module(SDL2TTF REQUIRED)
	include_directories(${SDL2TTF_INCLUDE_DIR})
endif()

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})

add_library(sdlclass STATIC 
	sdlclass.cpp
	sdlclass.hpp
)

target_include_directories(sdlclass PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
