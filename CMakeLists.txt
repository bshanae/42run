cmake_minimum_required(VERSION 3.15)
project(42run)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

set(ZLIB_LIBRARIES zlibstatic)
set(ENABLE_BOOST_WORKAROUND ON)
set(BUILD_STATIC_LIB ON)
set(BUILD_ASSIMP_TOOLS  ON)
set(ASSIMP_BUILD_STATIC_LIB ON)

add_subdirectory(project/external/glfw)
add_subdirectory(project/external/assimp)

include_directories(
	project/external/glad/include
	project/external/glfw/include
	project/external/assimp/include
	project/external/assimp/code
	project/external)

include_directories(
	project)

set(MAIN
	project/main.cpp)

set(ENGINE
	project/engine/core/core.cpp
	project/engine/core/start.cpp

	project/engine/program/shader.cpp
	project/engine/program/program.cpp

	project/engine/camera/camera.cpp

	project/engine/model/mesh.cpp

	project/engine/renderer/renderer.cpp)

add_executable(42run
	project/external/glad/src/glad.c
	${MAIN}
	${ENGINE})

target_link_libraries(42run glfw assimp)