PROJ_NAME := light

#LINUX (any posix probably idfk)
LIN_FLAGS := -g -std=c++20

LIN_DEPS := build_linux/release/engine/camera_component.o
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

LIN_DEPS += build_linux/release/game/entry.o
LIN_DEPS += build_linux/release/s7/s7.o


LIN_DEPS_DEBUG := build_linux/debug/engine/camera_component.o
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

LIN_DEPS_DEBUG += build_linux/debug/game/entry.o
LIN_DEPS_DEBUG += build_linux/debug/s7/s7.o

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
	gcc -c -o $@ $< -std=c++20 -g

build_linux/release/engine/%.o : src/engine/%.cpp
	g++ -c -o $@ $< -std=c++20
build_linux/release/game/%.o : src/game/%.cpp
	g++ -c -o $@ $< -std=c++20
build_linux/release/s7/%.o : src/s7/%.c
	gcc -c -o $@ $< -std=c++20

#WINDOWS
NT_FLAGS := /MT
NT_DEPS := build_windows/engine/camera_component.obj
NT_DEPS += build_windows/engine/component.obj
NT_DEPS += build_windows/engine/engine.obj
NT_DEPS += build_windows/engine/mesh.obj
NT_DEPS += build_windows/engine/opengl_renderer.obj
NT_DEPS += build_windows/engine/scene.obj
NT_DEPS += build_windows/engine/script_component.obj
NT_DEPS += build_windows/engine/shader.obj
NT_DEPS += build_windows/engine/texture.obj
NT_DEPS += build_windows/engine/transform.obj
NT_DEPS += build_windows/game/entry.obj
NT_DEPS += build_windows/s7/s7.obj

NT_LIBDIRS := /LIBPATH:"C:\\lib\\glfw\\lib"
NT_LIBDIRS += /LIBPATH:"C:\\lib\\glew\\lib"

NT_LIBS := glfw3.lib glew32s.lib opengl32.lib

windows_debug : $(NT_DEPS)
	link $(NT_DEPS)
windows : $(NT_DEPS)
	link $(NT_LIBDIRS) /OUT:"bin/windows/x64/debug/$(PROJ_NAME).exe" $(NT_DEPS) $(NT_LIBS)

build_windows/engine/camera_component.obj : src/engine/camera_component.cpp
	cl $(NT_FLAGS) /Fo".\\build_windows\\engine\\" /c "src\\engine\\camera_component.cpp"
build_windows/engine/component.obj : src/engine/component.cpp
	cl $(NT_FLAGS) /Fo".\\build_windows\\engine\\" /c "src\\engine\\component.cpp"
build_windows/engine/engine.obj : src/engine/engine.cpp
	cl $(NT_FLAGS) /Fo".\\build_windows\\engine\\" /c "src\\engine\\engine.cpp"
build_windows/engine/material.obj : src/engine/material.cpp
	cl $(NT_FLAGS) /Fo".\\build_windows\\engine\\" /c "src\\engine\\material.cpp"
build_windows/engine/mesh.obj : src/engine/mesh.cpp
	cl $(NT_FLAGS) /Fo".\\build_windows\\engine\\" /c "src\\engine\\mesh.cpp"
build_windows/engine/opengl_renderer.obj : src/engine/opengl_renderer.cpp
	cl $(NT_FLAGS) /Fo".\\build_windows\\engine\\" /c "src\\engine\\opengl_renderer.cpp"
build_windows/engine/scene.obj : src/engine/scene.cpp
	cl $(NT_FLAGS) /Fo".\\build_windows\\engine\\" /c "src\\engine\\scene.cpp"
build_windows/engine/script_component.obj : src/engine/script_component.cpp
	cl $(NT_FLAGS) /Fo".\\build_windows\\engine\\" /c "src\\engine\\script_component.cpp"
build_windows/engine/shader.obj : src/engine/shader.cpp
	cl $(NT_FLAGS) /Fo".\\build_windows\\engine\\" /c "src\\engine\\shader.cpp"
build_windows/engine/texture.obj : src/engine/texture.cpp
	cl $(NT_FLAGS) /Fo".\\build_windows\\engine\\" /c "src\\engine\\texture.cpp"
build_windows/engine/transform.obj : src/engine/transform.cpp
	cl $(NT_FLAGS) /Fo".\\build_windows\\engine\\" /c "src\\engine\\transform.cpp"
build_windows/game/entry.obj : src/game/entry.cpp
	cl $(NT_FLAGS) /Fo".\\build_windows\\game\\" /c "src\\game\\entry.cpp"
build_windows/s7/s7.obj : src/s7/s7.c
	cl $(NT_FLAGS) /std:c17 /DCLOCKS_PER_SEC=1000 /Fo".\\build_windows\\s7\\" /c /TC "src\\s7\\s7.c"
