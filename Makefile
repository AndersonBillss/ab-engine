BUILD_DIR := build/

DAWN_SRC := third_party/dawn
DAWN_OUT_DEBUG := $(BUILD_DIR)dawn/debug

.PHONY: dawn-debug dawn-debug-configure dawn-debug-build dawn-deps

dawn-debug-setup: dawn-deps dawn-debug-build

dawn-deps:
	cd $(DAWN_SRC) && python tools/fetch_dawn_dependencies.py

dawn-debug-configure:
	mkdir -p $(DAWN_OUT_DEBUG)
	cmake -S $(DAWN_SRC) \
	      -B $(DAWN_OUT_DEBUG) \
	      -GNinja \
	      -DCMAKE_BUILD_TYPE=Debug

dawn-debug-build: dawn-debug-configure
	cmake --build $(DAWN_OUT_DEBUG)