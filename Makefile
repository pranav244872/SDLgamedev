# Declare some Makefile variables
CC = g++
CC_WINDOWS = x86_64-w64-mingw32-g++
LANG_STD = -std=c++17
COMPILER_FLAGS = -Wall -Wfatal-errors
INCLUDE_PATH_LINUX = -I "./libs/"
INCLUDE_PATH_WINDOWS = -I "./libs/windows/include/" -I "./libs/sol/include/" -I "./libs/imgui/" -I "./libs/windows/include/SDL2"
SRC_FILES = $(wildcard ./src/*.cpp) \
            $(wildcard ./src/Game/*.cpp) \
            $(wildcard ./src/Logger/*.cpp) \
            $(wildcard ./src/ECS/*.cpp) \
            $(wildcard ./src/AssetStore/*.cpp) \
            $(wildcard ./libs/imgui/*.cpp) \
            ./src/Systems/LuaBindingFunctions.cpp

LINKER_FILES_LINUX = -l SDL2 -l SDL2_image -l SDL2_ttf -l lua5.4
LINKER_FILES_WINDOWS = -L "./libs/windows/lib" \
                       -l mingw32 \
                       -l SDL2main \
                       -l SDL2 \
                       -l SDL2_image \
                       -l SDL2_ttf \
                       -l lua

OBJ_NAME = gameengine
BUILD_DIR_LINUX = linux_build
BUILD_DIR_WINDOWS = windows_build

# Makefile Rules
all: build_linux build_windows

build_linux: $(BUILD_DIR_LINUX)/$(OBJ_NAME)
build_windows: $(BUILD_DIR_WINDOWS)/$(OBJ_NAME).exe

$(BUILD_DIR_LINUX)/$(OBJ_NAME): $(SRC_FILES)
	mkdir -p $(BUILD_DIR_LINUX)
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) $(INCLUDE_PATH_LINUX) $^ $(LINKER_FILES_LINUX) -o $@

$(BUILD_DIR_WINDOWS)/$(OBJ_NAME).exe: $(SRC_FILES)
	mkdir -p $(BUILD_DIR_WINDOWS)
	$(CC_WINDOWS) $(COMPILER_FLAGS) $(LANG_STD) $(INCLUDE_PATH_WINDOWS) $^ $(LINKER_FILES_WINDOWS) -o $@

run:
	./$(BUILD_DIR_LINUX)/$(OBJ_NAME)

clean:
	rm -rf $(BUILD_DIR_LINUX) $(BUILD_DIR_WINDOWS)

# New rule to generate compile_commands.json using 'bear'
comp_c:
	bear -- make build_linux

# Enable parallel build
.PHONY: all build_linux build_windows run clean comp_c
