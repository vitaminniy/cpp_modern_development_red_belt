all: build

BUILD_DIR = build

clean:
	rm -rf $(BUILD_DIR)
.PHONY: clean

cmake:
	cmake -B $(BUILD_DIR) -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
.PHONY: cmake

format: cmake
	cd $(BUILD_DIR) && make format
.PHONY: format

build: cmake
	cd $(BUILD_DIR) && cmake --build .
.PHONY: build

test: build
	cd $(BUILD_DIR) && make test
.PHONY: test
