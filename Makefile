BUILD_DIR := build/
ENGINE_OUT := $(BUILD_DIR)engine/

run-engine-debug: build-engine-debug
	./build/engine/ab_engine.exe

build-engine-debug:
	cmake -S . -B $(ENGINE_OUT) -GNinja \
  		-DCMAKE_C_COMPILER=cl \
  		-DCMAKE_CXX_COMPILER=cl
	cmake --build $(ENGINE_OUT)


DAWN_SRC := third_party/dawn
DAWN_OUT_DEBUG := $(BUILD_DIR)dawn/debug
DAWN_INSTALL_DEBUG := $(BUILD_DIR)_install/dawn/debug

.PHONY: dawn-debug dawn-debug-configure dawn-debug-build dawn-deps

dawn-debug-setup: dawn-deps dawn-debug-build

dawn-deps:
	cd $(DAWN_SRC) && python tools/fetch_dawn_dependencies.py

dawn-debug-configure:
	mkdir -p $(DAWN_OUT_DEBUG)
	cmake -S $(DAWN_SRC) \
	      -B $(DAWN_OUT_DEBUG) \
	      -GNinja \
		  -DCMAKE_C_COMPILER=cl \
		  -DCMAKE_CXX_COMPILER=cl \
	      -DCMAKE_BUILD_TYPE=Debug \
		  -DDAWN_ENABLE_INSTALL=ON

dawn-debug-build: dawn-debug-configure
	cmake --build $(DAWN_OUT_DEBUG)
	cmake --install $(DAWN_OUT_DEBUG) --prefix $(DAWN_INSTALL_DEBUG)
