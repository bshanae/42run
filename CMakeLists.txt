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

set(SOURCE_COMMON
	project/common/random/random.cpp)

set(SOURCE_ENGINE
	project/engine/engine.cpp

	project/engine/core/core.cpp
	project/engine/core/execute.cpp
	project/engine/core/process_x.cpp
	project/engine/core/callback.cpp
	project/engine/core/connect_with_global.cpp

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
	project/engine/model/group.cpp
	project/engine/model/manager.cpp

	project/engine/renderer/render.cpp
	project/engine/renderer/animate.cpp
	project/engine/renderer/connect_with_global.cpp
	project/engine/renderer/callback.cpp
	project/engine/renderer/data.cpp)

set(SOURCE_GAME
	project/game/game.cpp

	project/game/manager/manager.cpp

	project/game/room/room.cpp
	project/game/room/row.cpp
	project/game/room/update.cpp
	project/game/room/build_x.cpp
	project/game/room/x_offset_x.cpp
	project/game/room/spawn_x.cpp

	project/game/character/character.cpp)

set(SOURCE_MAIN
	project/main.cpp)

add_executable(42run
	${SOURCE_EXTERNAL}
	${SOURCE_COMMON}
	${SOURCE_ENGINE}
	${SOURCE_GAME}
	${SOURCE_MAIN})

target_link_libraries(42run glfw assimp image)