# Declare some Makefile variables

CC = g++

LANG_STD = -std=c++17

COMPILER_FLAGS = -Wall -Wfatal-errors

INCLUDE_PATH = -I "./libs/"

SRC_FILES = ./src/*.cpp \
	    ./src/Game/*.cpp \
	    ./src/Logger/*.cpp \
		./src/ECS/*.cpp \
		./src/AssetStore/*.cpp

LINKER_FILES = -l SDL2 -l SDL2_image -l SDL2_ttf -l lua5.4
OBJ_NAME = gameengine
  
# Makefile Rules

build:
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) $(INCLUDE_PATH) $(SRC_FILES) $(LINKER_FILES) -o $(OBJ_NAME)

run:
	./$(OBJ_NAME)

clean:
	rm $(OBJ_NAME)
