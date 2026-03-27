
mkdir build_windows\engine
mkdir build_windows\game
mkdir build_windows\s7
mkdir bin\windows\x64\debug
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
make windows
call "bin\\windows\\x64\\debug\\light.exe"
