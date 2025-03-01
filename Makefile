# source file directory
SRC_DIR = src
# file name for compiled binary
OBJ_NAME = play
# build directory
BUILD_DIR = build/debug

# Mac GCC COMPILER
CC = g++-12
# Windows GCC COMPILER
#CC = g++

# options
COMPILER_FLAGS = -std=c++17 -Wall -O0 -g

# source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

# Mac INCLUDE_PATHS
INCLUDE_PATHS = -Iinclude -I/usr/local/include
# Windows INCLUDE_PATHS
#INCLUDE_PATHS = -Iinclude -IC:/msys64/mingw64/include

# Mac LIBRARY_PATHS
LIBRARY_PATHS = -Llib -L/usr/local/lib
# Windows LIBRARY_PATHS
#LIBRARY_PATHS = -Llib -LC:/msys64/mingw64/lib

# Mac LINKER_FLAGS
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
# Windows LINKER_FLAGS
#LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf


all:
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) $(LINKER_FLAGS) -o $(BUILD_DIR)/$(OBJ_NAME)
