#						FUNCTIONS

define INFO
${info ${PREFIX} : $1}
endef

#						VARIABLES

COMMA = ,

OBJECT_FOLDER = .object
DEPEND_FOLDER = .depend

COMPILER = clang++
PREFIX = 42run
EXECUTABLE = 42run

INCLUDE = -I ../project/external -I ../project/external/stb -I ../project
OBJECT = ${OBJECT_FOLDER}/random.cpp.o ${OBJECT_FOLDER}/engine.cpp.o ${OBJECT_FOLDER}/core.cpp.o ${OBJECT_FOLDER}/execute.cpp.o ${OBJECT_FOLDER}/process_x.cpp.o ${OBJECT_FOLDER}/callback.cpp.o ${OBJECT_FOLDER}/use.cpp.o ${OBJECT_FOLDER}/time_x.cpp.o ${OBJECT_FOLDER}/use_depth_test.cpp.o ${OBJECT_FOLDER}/show_polygon_back.cpp.o ${OBJECT_FOLDER}/fill_polygon.cpp.o ${OBJECT_FOLDER}/default_settings.cpp.o ${OBJECT_FOLDER}/converter.cpp.o ${OBJECT_FOLDER}/shader.cpp.o ${OBJECT_FOLDER}/program.cpp.o ${OBJECT_FOLDER}/game_object.cpp.o ${OBJECT_FOLDER}/camera.cpp.o ${OBJECT_FOLDER}/scene.cpp.o ${OBJECT_FOLDER}/bone.cpp.o ${OBJECT_FOLDER}/skeleton.cpp.o ${OBJECT_FOLDER}/texture.cpp.o ${OBJECT_FOLDER}/mesh.cpp.o ${OBJECT_FOLDER}/model.cpp.o ${OBJECT_FOLDER}/instance.cpp.o ${OBJECT_FOLDER}/group.cpp.o ${OBJECT_FOLDER}/loader.cpp.o ${OBJECT_FOLDER}/game.cpp.o ${OBJECT_FOLDER}/manager.cpp.o ${OBJECT_FOLDER}/renderer.cpp.o ${OBJECT_FOLDER}/render.cpp.o ${OBJECT_FOLDER}/callback_1.cpp.o ${OBJECT_FOLDER}/x_uniforms.cpp.o ${OBJECT_FOLDER}/room.cpp.o ${OBJECT_FOLDER}/row.cpp.o ${OBJECT_FOLDER}/update.cpp.o ${OBJECT_FOLDER}/build_x.cpp.o ${OBJECT_FOLDER}/x_offset_x.cpp.o ${OBJECT_FOLDER}/spawn_x.cpp.o ${OBJECT_FOLDER}/character.cpp.o ${OBJECT_FOLDER}/UI.cpp.o ${OBJECT_FOLDER}/rectangle.cpp.o ${OBJECT_FOLDER}/renderer_1.cpp.o ${OBJECT_FOLDER}/symbol.cpp.o ${OBJECT_FOLDER}/renderer_2.cpp.o ${OBJECT_FOLDER}/font.cpp.o ${OBJECT_FOLDER}/manager_1.cpp.o ${OBJECT_FOLDER}/label.cpp.o ${OBJECT_FOLDER}/renderer_3.cpp.o ${OBJECT_FOLDER}/icon.cpp.o ${OBJECT_FOLDER}/frame.cpp.o ${OBJECT_FOLDER}/renderer_4.cpp.o ${OBJECT_FOLDER}/main.cpp.o
DEPEND = ${DEPEND_FOLDER}/random.cpp.d ${DEPEND_FOLDER}/engine.cpp.d ${DEPEND_FOLDER}/core.cpp.d ${DEPEND_FOLDER}/execute.cpp.d ${DEPEND_FOLDER}/process_x.cpp.d ${DEPEND_FOLDER}/callback.cpp.d ${DEPEND_FOLDER}/use.cpp.d ${DEPEND_FOLDER}/time_x.cpp.d ${DEPEND_FOLDER}/use_depth_test.cpp.d ${DEPEND_FOLDER}/show_polygon_back.cpp.d ${DEPEND_FOLDER}/fill_polygon.cpp.d ${DEPEND_FOLDER}/default_settings.cpp.d ${DEPEND_FOLDER}/converter.cpp.d ${DEPEND_FOLDER}/shader.cpp.d ${DEPEND_FOLDER}/program.cpp.d ${DEPEND_FOLDER}/game_object.cpp.d ${DEPEND_FOLDER}/camera.cpp.d ${DEPEND_FOLDER}/scene.cpp.d ${DEPEND_FOLDER}/bone.cpp.d ${DEPEND_FOLDER}/skeleton.cpp.d ${DEPEND_FOLDER}/texture.cpp.d ${DEPEND_FOLDER}/mesh.cpp.d ${DEPEND_FOLDER}/model.cpp.d ${DEPEND_FOLDER}/instance.cpp.d ${DEPEND_FOLDER}/group.cpp.d ${DEPEND_FOLDER}/loader.cpp.d ${DEPEND_FOLDER}/game.cpp.d ${DEPEND_FOLDER}/manager.cpp.d ${DEPEND_FOLDER}/renderer.cpp.d ${DEPEND_FOLDER}/render.cpp.d ${DEPEND_FOLDER}/callback_1.cpp.d ${DEPEND_FOLDER}/x_uniforms.cpp.d ${DEPEND_FOLDER}/room.cpp.d ${DEPEND_FOLDER}/row.cpp.d ${DEPEND_FOLDER}/update.cpp.d ${DEPEND_FOLDER}/build_x.cpp.d ${DEPEND_FOLDER}/x_offset_x.cpp.d ${DEPEND_FOLDER}/spawn_x.cpp.d ${DEPEND_FOLDER}/character.cpp.d ${DEPEND_FOLDER}/UI.cpp.d ${DEPEND_FOLDER}/rectangle.cpp.d ${DEPEND_FOLDER}/renderer_1.cpp.d ${DEPEND_FOLDER}/symbol.cpp.d ${DEPEND_FOLDER}/renderer_2.cpp.d ${DEPEND_FOLDER}/font.cpp.d ${DEPEND_FOLDER}/manager_1.cpp.d ${DEPEND_FOLDER}/label.cpp.d ${DEPEND_FOLDER}/renderer_3.cpp.d ${DEPEND_FOLDER}/icon.cpp.d ${DEPEND_FOLDER}/frame.cpp.d ${DEPEND_FOLDER}/renderer_4.cpp.d ${DEPEND_FOLDER}/main.cpp.d
LINK_DIRECTORY = 
LINK_LIBRARY = -l glfw -l glew -framework OpenGL -framework OpenCL

FLAG_OBJECT = `pkg-config --cflags glew` `pkg-config --cflags glfw3` `pkg-config --cflags freetype2` `pkg-config --cflags assimp`
FLAG_EXECUTABLE = `pkg-config --libs glew` `pkg-config --libs glfw3` `pkg-config --libs freetype2` `pkg-config --libs assimp`
FLAG_COMMON = -std=c++1z

#						BASIC RULES	

all : ${EXECUTABLE}

${EXECUTABLE} : ${OBJECT}
	${call INFO,Linking in executable ${EXECUTABLE}}
	@${COMPILER} ${FLAG_EXECUTABLE} ${FLAG_COMMON} ${LINK_DIRECTORY} ${LINK_LIBRARY} ${OBJECT} -o ${EXECUTABLE}

clean :
	${call INFO,Deleting objects' folder}
	@rm -rf ${OBJECT_FOLDER}
	${call INFO,Deleting dependencies' folder}
	@rm -rf ${DEPEND_FOLDER}

fclean : clean
	${call INFO,Deleting executable}
	@rm -rf ${EXECUTABLE}

re : fclean ${EXECUTABLE}

info :
	@echo "Objects :"
	@echo ${OBJECT}
	@echo "Depends :"
	@echo ${DEPEND}

.PHONY : clean fclean re info

#						OBJECTS
	
${OBJECT_FOLDER} :
	${call INFO,Creating objects' folder}
	@mkdir ${OBJECT_FOLDER}

${OBJECT_FOLDER}/random.cpp.o : ${DEPEND_FOLDER}/random.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,1%${COMMA} compiling object ../project/common/random/random.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/random.cpp.o -MF ${DEPEND_FOLDER}/random.cpp.d -c ../project/common/random/random.cpp -o ${OBJECT_FOLDER}/random.cpp.o

${OBJECT_FOLDER}/engine.cpp.o : ${DEPEND_FOLDER}/engine.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,3%${COMMA} compiling object ../project/engine/engine.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/engine.cpp.o -MF ${DEPEND_FOLDER}/engine.cpp.d -c ../project/engine/engine.cpp -o ${OBJECT_FOLDER}/engine.cpp.o

${OBJECT_FOLDER}/core.cpp.o : ${DEPEND_FOLDER}/core.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,5%${COMMA} compiling object ../project/engine/core/core.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/core.cpp.o -MF ${DEPEND_FOLDER}/core.cpp.d -c ../project/engine/core/core.cpp -o ${OBJECT_FOLDER}/core.cpp.o

${OBJECT_FOLDER}/execute.cpp.o : ${DEPEND_FOLDER}/execute.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,7%${COMMA} compiling object ../project/engine/core/execute.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/execute.cpp.o -MF ${DEPEND_FOLDER}/execute.cpp.d -c ../project/engine/core/execute.cpp -o ${OBJECT_FOLDER}/execute.cpp.o

${OBJECT_FOLDER}/process_x.cpp.o : ${DEPEND_FOLDER}/process_x.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,9%${COMMA} compiling object ../project/engine/core/process_x.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/process_x.cpp.o -MF ${DEPEND_FOLDER}/process_x.cpp.d -c ../project/engine/core/process_x.cpp -o ${OBJECT_FOLDER}/process_x.cpp.o

${OBJECT_FOLDER}/callback.cpp.o : ${DEPEND_FOLDER}/callback.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,11%${COMMA} compiling object ../project/engine/core/callback.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/callback.cpp.o -MF ${DEPEND_FOLDER}/callback.cpp.d -c ../project/engine/core/callback.cpp -o ${OBJECT_FOLDER}/callback.cpp.o

${OBJECT_FOLDER}/use.cpp.o : ${DEPEND_FOLDER}/use.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,13%${COMMA} compiling object ../project/engine/core/use.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/use.cpp.o -MF ${DEPEND_FOLDER}/use.cpp.d -c ../project/engine/core/use.cpp -o ${OBJECT_FOLDER}/use.cpp.o

${OBJECT_FOLDER}/time_x.cpp.o : ${DEPEND_FOLDER}/time_x.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,15%${COMMA} compiling object ../project/engine/core/time_x.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/time_x.cpp.o -MF ${DEPEND_FOLDER}/time_x.cpp.d -c ../project/engine/core/time_x.cpp -o ${OBJECT_FOLDER}/time_x.cpp.o

${OBJECT_FOLDER}/use_depth_test.cpp.o : ${DEPEND_FOLDER}/use_depth_test.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,17%${COMMA} compiling object ../project/engine/core/use_depth_test.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/use_depth_test.cpp.o -MF ${DEPEND_FOLDER}/use_depth_test.cpp.d -c ../project/engine/core/use_depth_test.cpp -o ${OBJECT_FOLDER}/use_depth_test.cpp.o

${OBJECT_FOLDER}/show_polygon_back.cpp.o : ${DEPEND_FOLDER}/show_polygon_back.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,19%${COMMA} compiling object ../project/engine/core/show_polygon_back.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/show_polygon_back.cpp.o -MF ${DEPEND_FOLDER}/show_polygon_back.cpp.d -c ../project/engine/core/show_polygon_back.cpp -o ${OBJECT_FOLDER}/show_polygon_back.cpp.o

${OBJECT_FOLDER}/fill_polygon.cpp.o : ${DEPEND_FOLDER}/fill_polygon.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,21%${COMMA} compiling object ../project/engine/core/fill_polygon.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/fill_polygon.cpp.o -MF ${DEPEND_FOLDER}/fill_polygon.cpp.d -c ../project/engine/core/fill_polygon.cpp -o ${OBJECT_FOLDER}/fill_polygon.cpp.o

${OBJECT_FOLDER}/default_settings.cpp.o : ${DEPEND_FOLDER}/default_settings.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,23%${COMMA} compiling object ../project/engine/core/default_settings.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/default_settings.cpp.o -MF ${DEPEND_FOLDER}/default_settings.cpp.d -c ../project/engine/core/default_settings.cpp -o ${OBJECT_FOLDER}/default_settings.cpp.o

${OBJECT_FOLDER}/converter.cpp.o : ${DEPEND_FOLDER}/converter.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,25%${COMMA} compiling object ../project/engine/converter/converter.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/converter.cpp.o -MF ${DEPEND_FOLDER}/converter.cpp.d -c ../project/engine/converter/converter.cpp -o ${OBJECT_FOLDER}/converter.cpp.o

${OBJECT_FOLDER}/shader.cpp.o : ${DEPEND_FOLDER}/shader.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,26%${COMMA} compiling object ../project/engine/program/shader.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/shader.cpp.o -MF ${DEPEND_FOLDER}/shader.cpp.d -c ../project/engine/program/shader.cpp -o ${OBJECT_FOLDER}/shader.cpp.o

${OBJECT_FOLDER}/program.cpp.o : ${DEPEND_FOLDER}/program.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,28%${COMMA} compiling object ../project/engine/program/program.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/program.cpp.o -MF ${DEPEND_FOLDER}/program.cpp.d -c ../project/engine/program/program.cpp -o ${OBJECT_FOLDER}/program.cpp.o

${OBJECT_FOLDER}/game_object.cpp.o : ${DEPEND_FOLDER}/game_object.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,30%${COMMA} compiling object ../project/engine/game_object/game_object.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/game_object.cpp.o -MF ${DEPEND_FOLDER}/game_object.cpp.d -c ../project/engine/game_object/game_object.cpp -o ${OBJECT_FOLDER}/game_object.cpp.o

${OBJECT_FOLDER}/camera.cpp.o : ${DEPEND_FOLDER}/camera.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,32%${COMMA} compiling object ../project/engine/scene/camera.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/camera.cpp.o -MF ${DEPEND_FOLDER}/camera.cpp.d -c ../project/engine/scene/camera.cpp -o ${OBJECT_FOLDER}/camera.cpp.o

${OBJECT_FOLDER}/scene.cpp.o : ${DEPEND_FOLDER}/scene.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,34%${COMMA} compiling object ../project/engine/scene/scene.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/scene.cpp.o -MF ${DEPEND_FOLDER}/scene.cpp.d -c ../project/engine/scene/scene.cpp -o ${OBJECT_FOLDER}/scene.cpp.o

${OBJECT_FOLDER}/bone.cpp.o : ${DEPEND_FOLDER}/bone.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,36%${COMMA} compiling object ../project/engine/model/bone.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/bone.cpp.o -MF ${DEPEND_FOLDER}/bone.cpp.d -c ../project/engine/model/bone.cpp -o ${OBJECT_FOLDER}/bone.cpp.o

${OBJECT_FOLDER}/skeleton.cpp.o : ${DEPEND_FOLDER}/skeleton.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,38%${COMMA} compiling object ../project/engine/model/skeleton.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/skeleton.cpp.o -MF ${DEPEND_FOLDER}/skeleton.cpp.d -c ../project/engine/model/skeleton.cpp -o ${OBJECT_FOLDER}/skeleton.cpp.o

${OBJECT_FOLDER}/texture.cpp.o : ${DEPEND_FOLDER}/texture.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,40%${COMMA} compiling object ../project/engine/model/texture.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/texture.cpp.o -MF ${DEPEND_FOLDER}/texture.cpp.d -c ../project/engine/model/texture.cpp -o ${OBJECT_FOLDER}/texture.cpp.o

${OBJECT_FOLDER}/mesh.cpp.o : ${DEPEND_FOLDER}/mesh.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,42%${COMMA} compiling object ../project/engine/model/mesh.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/mesh.cpp.o -MF ${DEPEND_FOLDER}/mesh.cpp.d -c ../project/engine/model/mesh.cpp -o ${OBJECT_FOLDER}/mesh.cpp.o

${OBJECT_FOLDER}/model.cpp.o : ${DEPEND_FOLDER}/model.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,44%${COMMA} compiling object ../project/engine/model/model.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/model.cpp.o -MF ${DEPEND_FOLDER}/model.cpp.d -c ../project/engine/model/model.cpp -o ${OBJECT_FOLDER}/model.cpp.o

${OBJECT_FOLDER}/instance.cpp.o : ${DEPEND_FOLDER}/instance.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,46%${COMMA} compiling object ../project/engine/model/instance.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/instance.cpp.o -MF ${DEPEND_FOLDER}/instance.cpp.d -c ../project/engine/model/instance.cpp -o ${OBJECT_FOLDER}/instance.cpp.o

${OBJECT_FOLDER}/group.cpp.o : ${DEPEND_FOLDER}/group.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,48%${COMMA} compiling object ../project/engine/model/group.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/group.cpp.o -MF ${DEPEND_FOLDER}/group.cpp.d -c ../project/engine/model/group.cpp -o ${OBJECT_FOLDER}/group.cpp.o

${OBJECT_FOLDER}/loader.cpp.o : ${DEPEND_FOLDER}/loader.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,50%${COMMA} compiling object ../project/engine/model/loader.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/loader.cpp.o -MF ${DEPEND_FOLDER}/loader.cpp.d -c ../project/engine/model/loader.cpp -o ${OBJECT_FOLDER}/loader.cpp.o

${OBJECT_FOLDER}/game.cpp.o : ${DEPEND_FOLDER}/game.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,51%${COMMA} compiling object ../project/game/game.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/game.cpp.o -MF ${DEPEND_FOLDER}/game.cpp.d -c ../project/game/game.cpp -o ${OBJECT_FOLDER}/game.cpp.o

${OBJECT_FOLDER}/manager.cpp.o : ${DEPEND_FOLDER}/manager.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,53%${COMMA} compiling object ../project/game/manager/manager.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/manager.cpp.o -MF ${DEPEND_FOLDER}/manager.cpp.d -c ../project/game/manager/manager.cpp -o ${OBJECT_FOLDER}/manager.cpp.o

${OBJECT_FOLDER}/renderer.cpp.o : ${DEPEND_FOLDER}/renderer.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,55%${COMMA} compiling object ../project/game/renderer/renderer.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/renderer.cpp.o -MF ${DEPEND_FOLDER}/renderer.cpp.d -c ../project/game/renderer/renderer.cpp -o ${OBJECT_FOLDER}/renderer.cpp.o

${OBJECT_FOLDER}/render.cpp.o : ${DEPEND_FOLDER}/render.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,57%${COMMA} compiling object ../project/game/renderer/render.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/render.cpp.o -MF ${DEPEND_FOLDER}/render.cpp.d -c ../project/game/renderer/render.cpp -o ${OBJECT_FOLDER}/render.cpp.o

${OBJECT_FOLDER}/callback_1.cpp.o : ${DEPEND_FOLDER}/callback_1.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,59%${COMMA} compiling object ../project/game/renderer/callback.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/callback_1.cpp.o -MF ${DEPEND_FOLDER}/callback_1.cpp.d -c ../project/game/renderer/callback.cpp -o ${OBJECT_FOLDER}/callback_1.cpp.o

${OBJECT_FOLDER}/x_uniforms.cpp.o : ${DEPEND_FOLDER}/x_uniforms.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,61%${COMMA} compiling object ../project/game/renderer/x_uniforms.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/x_uniforms.cpp.o -MF ${DEPEND_FOLDER}/x_uniforms.cpp.d -c ../project/game/renderer/x_uniforms.cpp -o ${OBJECT_FOLDER}/x_uniforms.cpp.o

${OBJECT_FOLDER}/room.cpp.o : ${DEPEND_FOLDER}/room.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,63%${COMMA} compiling object ../project/game/room/room.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/room.cpp.o -MF ${DEPEND_FOLDER}/room.cpp.d -c ../project/game/room/room.cpp -o ${OBJECT_FOLDER}/room.cpp.o

${OBJECT_FOLDER}/row.cpp.o : ${DEPEND_FOLDER}/row.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,65%${COMMA} compiling object ../project/game/room/row.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/row.cpp.o -MF ${DEPEND_FOLDER}/row.cpp.d -c ../project/game/room/row.cpp -o ${OBJECT_FOLDER}/row.cpp.o

${OBJECT_FOLDER}/update.cpp.o : ${DEPEND_FOLDER}/update.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,67%${COMMA} compiling object ../project/game/room/update.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/update.cpp.o -MF ${DEPEND_FOLDER}/update.cpp.d -c ../project/game/room/update.cpp -o ${OBJECT_FOLDER}/update.cpp.o

${OBJECT_FOLDER}/build_x.cpp.o : ${DEPEND_FOLDER}/build_x.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,69%${COMMA} compiling object ../project/game/room/build_x.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/build_x.cpp.o -MF ${DEPEND_FOLDER}/build_x.cpp.d -c ../project/game/room/build_x.cpp -o ${OBJECT_FOLDER}/build_x.cpp.o

${OBJECT_FOLDER}/x_offset_x.cpp.o : ${DEPEND_FOLDER}/x_offset_x.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,71%${COMMA} compiling object ../project/game/room/x_offset_x.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/x_offset_x.cpp.o -MF ${DEPEND_FOLDER}/x_offset_x.cpp.d -c ../project/game/room/x_offset_x.cpp -o ${OBJECT_FOLDER}/x_offset_x.cpp.o

${OBJECT_FOLDER}/spawn_x.cpp.o : ${DEPEND_FOLDER}/spawn_x.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,73%${COMMA} compiling object ../project/game/room/spawn_x.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/spawn_x.cpp.o -MF ${DEPEND_FOLDER}/spawn_x.cpp.d -c ../project/game/room/spawn_x.cpp -o ${OBJECT_FOLDER}/spawn_x.cpp.o

${OBJECT_FOLDER}/character.cpp.o : ${DEPEND_FOLDER}/character.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,75%${COMMA} compiling object ../project/game/character/character.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/character.cpp.o -MF ${DEPEND_FOLDER}/character.cpp.d -c ../project/game/character/character.cpp -o ${OBJECT_FOLDER}/character.cpp.o

${OBJECT_FOLDER}/UI.cpp.o : ${DEPEND_FOLDER}/UI.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,76%${COMMA} compiling object ../project/UI/UI.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/UI.cpp.o -MF ${DEPEND_FOLDER}/UI.cpp.d -c ../project/UI/UI.cpp -o ${OBJECT_FOLDER}/UI.cpp.o

${OBJECT_FOLDER}/rectangle.cpp.o : ${DEPEND_FOLDER}/rectangle.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,78%${COMMA} compiling object ../project/UI/rectangle/rectangle.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/rectangle.cpp.o -MF ${DEPEND_FOLDER}/rectangle.cpp.d -c ../project/UI/rectangle/rectangle.cpp -o ${OBJECT_FOLDER}/rectangle.cpp.o

${OBJECT_FOLDER}/renderer_1.cpp.o : ${DEPEND_FOLDER}/renderer_1.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,80%${COMMA} compiling object ../project/UI/rectangle/renderer.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/renderer_1.cpp.o -MF ${DEPEND_FOLDER}/renderer_1.cpp.d -c ../project/UI/rectangle/renderer.cpp -o ${OBJECT_FOLDER}/renderer_1.cpp.o

${OBJECT_FOLDER}/symbol.cpp.o : ${DEPEND_FOLDER}/symbol.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,82%${COMMA} compiling object ../project/UI/font/symbol.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/symbol.cpp.o -MF ${DEPEND_FOLDER}/symbol.cpp.d -c ../project/UI/font/symbol.cpp -o ${OBJECT_FOLDER}/symbol.cpp.o

${OBJECT_FOLDER}/renderer_2.cpp.o : ${DEPEND_FOLDER}/renderer_2.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,84%${COMMA} compiling object ../project/UI/font/renderer.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/renderer_2.cpp.o -MF ${DEPEND_FOLDER}/renderer_2.cpp.d -c ../project/UI/font/renderer.cpp -o ${OBJECT_FOLDER}/renderer_2.cpp.o

${OBJECT_FOLDER}/font.cpp.o : ${DEPEND_FOLDER}/font.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,86%${COMMA} compiling object ../project/UI/font/font.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/font.cpp.o -MF ${DEPEND_FOLDER}/font.cpp.d -c ../project/UI/font/font.cpp -o ${OBJECT_FOLDER}/font.cpp.o

${OBJECT_FOLDER}/manager_1.cpp.o : ${DEPEND_FOLDER}/manager_1.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,88%${COMMA} compiling object ../project/UI/font/manager.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/manager_1.cpp.o -MF ${DEPEND_FOLDER}/manager_1.cpp.d -c ../project/UI/font/manager.cpp -o ${OBJECT_FOLDER}/manager_1.cpp.o

${OBJECT_FOLDER}/label.cpp.o : ${DEPEND_FOLDER}/label.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,90%${COMMA} compiling object ../project/UI/label/label.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/label.cpp.o -MF ${DEPEND_FOLDER}/label.cpp.d -c ../project/UI/label/label.cpp -o ${OBJECT_FOLDER}/label.cpp.o

${OBJECT_FOLDER}/renderer_3.cpp.o : ${DEPEND_FOLDER}/renderer_3.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,92%${COMMA} compiling object ../project/UI/label/renderer.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/renderer_3.cpp.o -MF ${DEPEND_FOLDER}/renderer_3.cpp.d -c ../project/UI/label/renderer.cpp -o ${OBJECT_FOLDER}/renderer_3.cpp.o

${OBJECT_FOLDER}/icon.cpp.o : ${DEPEND_FOLDER}/icon.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,94%${COMMA} compiling object ../project/UI/icon/icon.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/icon.cpp.o -MF ${DEPEND_FOLDER}/icon.cpp.d -c ../project/UI/icon/icon.cpp -o ${OBJECT_FOLDER}/icon.cpp.o

${OBJECT_FOLDER}/frame.cpp.o : ${DEPEND_FOLDER}/frame.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,96%${COMMA} compiling object ../project/UI/frame/frame.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/frame.cpp.o -MF ${DEPEND_FOLDER}/frame.cpp.d -c ../project/UI/frame/frame.cpp -o ${OBJECT_FOLDER}/frame.cpp.o

${OBJECT_FOLDER}/renderer_4.cpp.o : ${DEPEND_FOLDER}/renderer_4.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,98%${COMMA} compiling object ../project/UI/frame/renderer.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/renderer_4.cpp.o -MF ${DEPEND_FOLDER}/renderer_4.cpp.d -c ../project/UI/frame/renderer.cpp -o ${OBJECT_FOLDER}/renderer_4.cpp.o

${OBJECT_FOLDER}/main.cpp.o : ${DEPEND_FOLDER}/main.cpp.d | ${OBJECT_FOLDER} ${DEPEND_FOLDER}
	${call INFO,100%${COMMA} compiling object ../project/main.cpp}
	@${COMPILER} ${INCLUDE} ${FLAG_OBJECT} ${FLAG_COMMON} -MMD -MP -MT ${OBJECT_FOLDER}/main.cpp.o -MF ${DEPEND_FOLDER}/main.cpp.d -c ../project/main.cpp -o ${OBJECT_FOLDER}/main.cpp.o
	

#						DEPENDENCIES

${DEPEND_FOLDER} :
	${call INFO,Creating dependencies' folder}
	@mkdir ${DEPEND_FOLDER}
	
${DEPEND} :

include ${wildcard ${DEPEND}}	
