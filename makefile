PROJ_NAME := light



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

windows_debug : $(NT_DEPS)
	link $(NT_DEPS)
windows : $(NT_DEPS)
	link /OUT:"bin/windows/x64/debug/$(PROJ_NAME).exe" $(NT_DEPS)



build_windows/engine/camera_component.obj : src/engine/camera_component.cpp
	cl /MT /Fo".\\build_windows\\engine\\" /c "src\\engine\\camera_component.cpp"
build_windows/engine/component.obj : src/engine/component.cpp
	cl /MT /Fo".\\build_windows\\engine\\" /c "src\\engine\\component.cpp"
build_windows/engine/engine.obj : src/engine/engine.cpp
	cl /MT /Fo".\\build_windows\\engine\\" /c "src\\engine\\engine.cpp"
build_windows/engine/mesh.obj : src/engine/mesh.cpp
	cl /MT /Fo".\\build_windows\\engine\\" /c "src\\engine\\mesh.cpp"
build_windows/engine/opengl_renderer.obj : src/engine/opengl_renderer.cpp
	cl /MT /Fo".\\build_windows\\engine\\" /c "src\\engine\\opengl_renderer.cpp"
build_windows/engine/scene.obj : src/engine/scene.cpp
	cl /MT /Fo".\\build_windows\\engine\\" /c "src\\engine\\scene.cpp"
build_windows/engine/script_component.obj : src/engine/script_component.cpp
	cl /MT /Fo".\\build_windows\\engine\\" /c "src\\engine\\script_component.cpp"
build_windows/engine/shader.obj : src/engine/shader.cpp
	cl /MT /Fo".\\build_windows\\engine\\" /c "src\\engine\\shader.cpp"
build_windows/engine/texture.obj : src/engine/texture.cpp
	cl /MT /Fo".\\build_windows\\engine\\" /c "src\\engine\\texture.cpp"
build_windows/engine/transform.obj : src/engine/transform.cpp
	cl /MT /Fo".\\build_windows\\engine\\" /c "src\\engine\\transform.cpp"
build_windows/game/entry.obj : src/game/entry.cpp
	cl /MT /Fo".\\build_windows\\game\\" /c "src\\game\\entry.cpp"
