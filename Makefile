# Makefile for CMake-based projects

CMAKE = cmake
BUILD_DIR = build

all: test

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

test: compile
	ctest   --test-dir build

configure: $(BUILD_DIR)
	$(CMAKE) -S . -B $(BUILD_DIR)

compile: configure
	$(CMAKE) --build $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

format:
	find . -regex '.*\.\(cpp\|hpp\|cc\|cxx\)' -exec clang-format -style=file -i {} \;

.PHONY: all configure compile clean format test

