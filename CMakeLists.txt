cmake_minimum_required(VERSION 3.25)

project(
	maths
	VERSION 0.0.1
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)

set(
	maths_sources
	"src/main.cpp"
	"src/types/integer.h"
	"src/types/integer.cpp"
	"src/ui/terminal.h"
	"src/ui/terminal.cpp"
)

add_executable(maths ${maths_sources})