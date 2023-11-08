# Makefile for CMake-based projects

CMAKE = cmake
BUILD_DIR = build

UNAME := $(shell uname)

all: test

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

test: compile
	ctest -V --test-dir build

configure: $(BUILD_DIR)
	$(CMAKE) -S . -B $(BUILD_DIR)

compile: configure
	$(CMAKE) --build $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

ifeq ($(UNAME), Darwin)
# macOS specific formatting
format:
	find . -type f \( -name "*.cpp" -o -name "*.hpp" -o -name "*.cc" -o -name "*.cxx" -o -name "*.h" \) -exec clang-format -style=file -i {} \;
else
# Other platforms use the original command
format:
	find . -regex '.*\.\(cpp\|hpp\|cc\|cxx\|h\)' -exec clang-format -style=file -i {} \;
endif

.PHONY: all configure compile clean format test
