
mkdir build_windows\engine
mkdir build_windows\game
mkdir build_windows\s7
mkdir build_windows\imgui
mkdir bin\windows\x64\debug
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
make windows_debug -j 6
mkdir deploy
copy ".\bin\windows\x64\debug\light.exe" ".\light.exe"
