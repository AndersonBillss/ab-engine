
all: run

run: build
	./build/bin/program.exe

build:
	@mkdir -p ./build
	@mkdir -p ./build/bin
	g++ -Wall -Wextra source/main.cpp -IC:/msys64/mingw64/include/GLFW -lglfw3 -o ./build/bin/program.exe

clean:
	rm -rf build
