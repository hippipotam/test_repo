cmake_minimum_required(VERSION 2.8)

project(helloworld)

add_executable(helloworld main.cpp)

find_package (SDL2 REQUIRED)
if (SDL2_FOUND)
	include_directories(${SDL2_INCLUDE_DIRS})
	target_link_libraries (helloworld ${SDL2_LIBRARIES})
endif (SDL2_FOUND)
