# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++17 -I/usr/include/freetype2

# Libraries
LIBS = -lglfw -lGL -lGLU -lGLEW -lfreetype

# Source files
SRC = src/main.cpp src/glad.c src/shape.cpp src/game.cpp src/shader.cpp src/layout.cpp src/constants.cpp src/snake.cpp src/utils.cpp src/text.cpp

# Output binary
OUT = main

# Include directories
INCLUDES = -Iinclude

# Build the project
all: $(SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(OUT) $(SRC) $(LIBS)

# Clean the build
clean:
	rm -f $(OUT)
