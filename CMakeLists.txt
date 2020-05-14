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
add_subdirectory(project/external/stb)

include_directories(
	project/external
	project/external/glad/include
	project/external/glfw/include
	project/external/assimp/include
	project/external/assimp/code
	project/external/stb)

include_directories(
	project)

set(SOURCE_EXTERNAL
	project/external/glad/src/glad.c)

set(SOURCE_MAIN
	project/main.cpp)

set(SOURCE_ENGINE
	project/engine/core/core.cpp
	project/engine/core/execute.cpp
	project/engine/core/callback.cpp
	project/engine/core/connect_renderer.cpp

	project/engine/converter/converter.cpp

	project/engine/program/shader.cpp
	project/engine/program/program.cpp

	project/engine/scene/camera.cpp

	project/engine/model/bone.cpp
	project/engine/model/skeleton.cpp
	project/engine/model/texture.cpp
	project/engine/model/mesh.cpp
	project/engine/model/model.cpp
	project/engine/model/instance.cpp
	project/engine/model/manager.cpp

	project/engine/renderer/renderer.cpp
	)

add_executable(42run
	${SOURCE_EXTERNAL}
	${SOURCE_MAIN}
	${SOURCE_ENGINE})

target_link_libraries(42run glfw assimp image)