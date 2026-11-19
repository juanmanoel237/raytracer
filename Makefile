# Shortcuts for Linux, macOS and the dev container. See docs/adr/0004-makefile.md
# On Windows, use the presets directly (see README).
PRESET ?= unix-debug

.PHONY: build run test clean

build:
	cmake --preset $(PRESET)
	cmake --build --preset $(PRESET)

run: build
	./build/$(PRESET)/raytracer

test: build
	ctest --preset $(PRESET)

clean:
	rm -rf build/$(PRESET)
