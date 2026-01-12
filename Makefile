BUILD_DIR = ./build/

all: run

run: build
	./build/bin/program.exe

build:
	@mkdir -p ./build
	@mkdir -p ./build/bin
	g++ -Wall -Wextra source/main.cpp -IC:/msys64/mingw64/include/GLFW -lglfw3 -o ./build/bin/program.exe

clean:
	rm -rf build

DAWN_SRC := third_party/dawn
DAWN_OUT := $(BUILD_DIR)/dawn

dawn-initial-setup: dawn-deps dawn-build

dawn-deps:
	cd $(DAWN_SRC) && python tools/fetch_dawn_dependencies.py

dawn-configure:
	mkdir -p ../../$(DAWN_OUT)
	cd $(DAWN_SRC) && cmake -GNinja ../../$(DAWN_OUT)

dawn-build: dawn-configure
	cd $(DAWN_SRC) && cmake --build .
	