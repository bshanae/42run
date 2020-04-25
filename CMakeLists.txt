cmake_minimum_required(VERSION 3.15)
project(42run)

set(CMAKE_CXX_STANDARD 17)

include_directories(
	project)

include_directories(
	/usr/local/include
	/opt/local/include)

link_directories(
	/usr/local/lib
	/opt/local/lib)

link_libraries(
	"-framework OpenGL"
	"-framework OpenCL"
	GLFW
	GLEW)

set(MAIN
	project/main.cpp)

set(ENGINE
	project/engine/core/core.cpp
	project/engine/core/start.cpp)

add_executable(42run
	${MAIN}
	${ENGINE})