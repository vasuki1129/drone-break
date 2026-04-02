PROJ_NAME := light

#LINUX (any posix probably idfk)
LIN_FLAGS := -g -std=c++20 -w

LIN_DEPS := build_linux/release/engine/camera_component.o
LIN_DEPS += build_linux/release/engine/mesh_component.o
LIN_DEPS += build_linux/release/engine/component.o
LIN_DEPS += build_linux/release/engine/engine.o
LIN_DEPS += build_linux/release/engine/mesh.o
LIN_DEPS += build_linux/release/engine/model.o
LIN_DEPS += build_linux/release/engine/opengl_renderer.o
LIN_DEPS += build_linux/release/engine/scene.o
LIN_DEPS += build_linux/release/engine/script_component.o
LIN_DEPS += build_linux/release/engine/shader.o
LIN_DEPS += build_linux/release/engine/texture.o
LIN_DEPS += build_linux/release/engine/transform.o
LIN_DEPS += build_linux/release/engine/material.o
LIN_DEPS += build_linux/release/engine/util.o
LIN_DEPS += build_linux/release/engine/scene_loader.o
LIN_DEPS += build_linux/release/engine/editor.o
LIN_DEPS += build_linux/release/engine/asset.o
LIN_DEPS += build_linux/release/engine/asset_manager.o


LIN_DEPS += build_linux/release/game/entry.o

LIN_DEPS += build_linux/release/s7/s7.o

LIN_DEPS += build_linux/release/imgui/imgui.o
LIN_DEPS += build_linux/release/imgui/imgui_demo.o
LIN_DEPS += build_linux/release/imgui/imgui_draw.o
LIN_DEPS += build_linux/release/imgui/imgui_impl_glfw.o
LIN_DEPS += build_linux/release/imgui/imgui_impl_opengl3.o
LIN_DEPS += build_linux/release/imgui/imgui_tables.o
LIN_DEPS += build_linux/release/imgui/imgui_widgets.o

LIN_DEPS_DEBUG := build_linux/debug/engine/camera_component.o
LIN_DEPS_DEBUG += build_linux/debug/engine/mesh_component.o
LIN_DEPS_DEBUG += build_linux/debug/engine/component.o
LIN_DEPS_DEBUG += build_linux/debug/engine/engine.o
LIN_DEPS_DEBUG += build_linux/debug/engine/mesh.o
LIN_DEPS_DEBUG += build_linux/debug/engine/model.o
LIN_DEPS_DEBUG += build_linux/debug/engine/opengl_renderer.o
LIN_DEPS_DEBUG += build_linux/debug/engine/scene.o
LIN_DEPS_DEBUG += build_linux/debug/engine/script_component.o
LIN_DEPS_DEBUG += build_linux/debug/engine/shader.o
LIN_DEPS_DEBUG += build_linux/debug/engine/texture.o
LIN_DEPS_DEBUG += build_linux/debug/engine/transform.o
LIN_DEPS_DEBUG += build_linux/debug/engine/material.o
LIN_DEPS_DEBUG += build_linux/debug/engine/util.o
LIN_DEPS_DEBUG += build_linux/debug/engine/scene_loader.o
LIN_DEPS_DEBUG += build_linux/debug/engine/editor.o
LIN_DEPS_DEBUG += build_linux/debug/engine/asset.o
LIN_DEPS_DEBUG += build_linux/debug/engine/asset_manager.o

LIN_DEPS_DEBUG += build_linux/debug/game/entry.o

LIN_DEPS_DEBUG += build_linux/debug/s7/s7.o

LIN_DEPS_DEBUG += build_linux/debug/imgui/imgui.o
LIN_DEPS_DEBUG += build_linux/debug/imgui/imgui_demo.o
LIN_DEPS_DEBUG += build_linux/debug/imgui/imgui_draw.o
LIN_DEPS_DEBUG += build_linux/debug/imgui/imgui_impl_glfw.o
LIN_DEPS_DEBUG += build_linux/debug/imgui/imgui_impl_opengl3.o
LIN_DEPS_DEBUG += build_linux/debug/imgui/imgui_tables.o
LIN_DEPS_DEBUG += build_linux/debug/imgui/imgui_widgets.o


LIN_LIBS := -lglfw -lGLEW -lGL -lassimp

linux_all : linux_debug linux

linux_debug : $(LIN_DEPS_DEBUG)
	g++ $(LIN_DEPS_DEBUG) -o bin/linux/x64/debug/light $(LIN_LIBS) -g
linux : $(LIN_DEPS)
	g++ $(LIN_DEPS) -o bin/linux/x64/release/light $(LIN_LIBS)

build_linux/debug/engine/%.o : src/engine/%.cpp
	g++ -c -o $@ $< -std=c++20 -g
build_linux/debug/game/%.o : src/game/%.cpp
	g++ -c -o $@ $< -std=c++20 -g
build_linux/debug/s7/%.o : src/s7/%.c
	gcc -c -o $@ $< -g
build_linux/debug/imgui/%.o : src/imgui/%.cpp
	g++ -c -o $@ $< -std=c++20 -g

build_linux/release/engine/%.o : src/engine/%.cpp
	g++ -c -o $@ $< -std=c++20
build_linux/release/game/%.o : src/game/%.cpp
	g++ -c -o $@ $< -std=c++20
build_linux/release/s7/%.o : src/s7/%.c
	gcc -c -o $@ $<
build_linux/release/imgui/%.o : src/imgui/%.cpp
	g++ -c -o $@ $< -std=c++20

#WINDOWS
NT_FLAGS := /DGLEW_STATIC /MDd /EHsc /IC:\lib\glm\include /IC:\lib\glew\include /IC:\lib\glfw\include /IC:\lib\assimp\include
NT_DEPS := build_windows/engine/camera_component.obj
NT_DEPS += build_windows/engine/component.obj
NT_DEPS += build_windows/engine/engine.obj
NT_DEPS += build_windows/engine/mesh.obj
NT_DEPS += build_windows/engine/model.obj
NT_DEPS += build_windows/engine/opengl_renderer.obj
NT_DEPS += build_windows/engine/scene.obj
NT_DEPS += build_windows/engine/script_component.obj
NT_DEPS += build_windows/engine/shader.obj
NT_DEPS += build_windows/engine/texture.obj
NT_DEPS += build_windows/engine/transform.obj
NT_DEPS += build_windows/engine/material.obj
NT_DEPS += build_windows/engine/util.obj
NT_DEPS += build_windows/engine/scene_loader.obj
NT_DEPS += build_windows/engine/editor.o


NT_DEPS += build_windows/game/entry.obj

NT_DEPS += build_windows/s7/s7.obj

NT_DEPS += build_windows/imgui/imgui.obj
NT_DEPS += build_windows/imgui/imgui_demo.obj
NT_DEPS += build_windows/imgui/imgui_draw.obj
NT_DEPS += build_windows/imgui/imgui_impl_glfw.obj
NT_DEPS += build_windows/imgui/imgui_impl_opengl3.obj
NT_DEPS += build_windows/imgui/imgui_tables.obj
NT_DEPS += build_windows/imgui/imgui_widgets.obj

NT_LIBDIRS := /LIBPATH:"C:\\lib\\glfw\\lib"
NT_LIBDIRS += /LIBPATH:"C:\\lib\\glew\\lib"
NT_LIBDIRS += /LIBPATH:"C:\\lib\\assimp\\lib\\x64"

NT_LIBS := glfw3.lib glew32s.lib opengl32.lib assimp-vc143-mt.lib Gdi32.lib

windows_debug : $(NT_DEPS)
	link $(NT_DEPS)
windows : $(NT_DEPS)
	link $(NT_LIBDIRS) /OUT:"bin/windows/x64/debug/$(PROJ_NAME).exe" $(NT_DEPS) $(NT_LIBS)

build_windows/engine/%.obj : src/engine/%.cpp
	cl /std:c++20 $(NT_FLAGS) /Fo$@ /c $<
build_windows/s7/s7.obj : src/s7/s7.c
	cl $(NT_FLAGS) /std:c17 /DCLOCKS_PER_SEC=1000 /Fo".\\build_windows\\s7\\" /c /TC "src\\s7\\s7.c"

build_windows/imgui/%.obj : src/imgui/%.cpp
	cl /std:c++20 $(NT_FLAGS) /Fo$@ /c $<

build_windows/game/%.obj : src/game/%.cpp
	cl /std:c++20 $(NT_FLAGS) /Fo$@ /c $<
