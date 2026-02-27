cmake_minimum_required(VERSION 3.16)

project(img_test
	VERSION 1.0
	LANGUAGES C)

set(CMAKE_C_STANDARD 11)

add_library(img_lib img.c img.h)

add_executable(img_test test.c)

target_include_directories(img_test PRIVATE 
	${CMAKE_CURRENT_SOURCE_DIR}/sokol
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(img_test PRIVATE
	m
	pthread
	dl
	GL
	X11
	Xi
	Xcursor
	img_lib
)
