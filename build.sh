mkdir -p build_linux/debug/game
mkdir -p build_linux/debug/engine
mkdir -p build_linux/debug/s7

mkdir -p build_linux/release/game
mkdir -p build_linux/release/engine
mkdir -p build_linux/release/s7

mkdir -p bin/linux/x64/release
mkdir -p bin/linux/x64/debug

make linux_all
