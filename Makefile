all: build

BUILD_DIR = build

clean:
	rm -rf $(BUILD_DIR)
.PHONY: clean

format:
	find src/ -type f -name "*.h" -print 	| xargs clang-format -i
	find src/ -type f -name "*.hpp" -print 	| xargs clang-format -i
	find src/ -type f -name "*.cpp" -print 	| xargs clang-format -i
.PHONY: format

build:
	cmake -B $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake --build .
.PHONY: build

test: build
	cd $(BUILD_DIR) && make test
.PHONY: test
