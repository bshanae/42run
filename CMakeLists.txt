cmake_minimum_required(VERSION 3.16)
project(42run)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Winline")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(ASSIMP REQUIRED)
find_package(FREETYPE REQUIRED)

#add_subdirectory(project/external/stb)

include_directories(/usr/local/include)

link_directories(/usr/local/lib)

include_directories(
	project/external
	project/external/stb
	project)

set(SOURCE_COMMON
	project/common/random/random.cpp)

set(SOURCE_ENGINE
	project/engine/engine.cpp

	project/engine/core/core.cpp
	project/engine/core/execute.cpp
	project/engine/core/process_x.cpp
	project/engine/core/callback.cpp

	project/engine/converter/converter.cpp

	project/engine/program/shader.cpp
	project/engine/program/program.cpp

	project/engine/scene/camera.cpp
	project/engine/scene/scene.cpp

	project/engine/model/bone.cpp
	project/engine/model/skeleton.cpp
	project/engine/model/texture.cpp
	project/engine/model/mesh.cpp
	project/engine/model/model.cpp
	project/engine/model/instance.cpp
	project/engine/model/group.cpp
	project/engine/model/manager.cpp)

set(SOURCE_GAME
	project/game/game.cpp

	project/game/manager/manager.cpp

	project/game/renderer/renderer.cpp
	project/game/renderer/render.cpp
	project/game/renderer/callback.cpp
	project/game/renderer/x_uniforms.cpp

	project/game/room/room.cpp
	project/game/room/row.cpp
	project/game/room/update.cpp
	project/game/room/build_x.cpp
	project/game/room/x_offset_x.cpp
	project/game/room/spawn_x.cpp

	project/game/character/character.cpp)

set(SOURCE_UI
	project/UI/font/font.cpp
	project/UI/font/symbol.cpp)

set(SOURCE_MAIN
	project/main.cpp)

add_executable(42run
	${SOURCE_COMMON}
	${SOURCE_ENGINE}
	${SOURCE_UI}
	${SOURCE_GAME}
	${SOURCE_MAIN})

target_link_libraries(42run ${OPENGL_LIBRARIES})
target_link_libraries(42run glfw)
target_link_libraries(42run glew)
target_link_libraries(42run ${FREETYPE_LIBRARIES})
target_link_libraries(42run ${ASSIMP_LIBRARIES})

target_link_directories(42run PRIVATE ${ASSIMP_LIBRARY_DIRS})

target_include_directories(42run PRIVATE ${OPENGL_INCLUDE_DIRS})
target_include_directories(42run PRIVATE ${GLEW_INCLUDE_DIRS})
target_include_directories(42run PRIVATE ${ASSIMP_INCLUDE_DIRS})
target_include_directories(42run PRIVATE ${FREETYPE_INCLUDE_DIRS})