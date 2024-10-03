# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++17

# Libraries
LIBS = -lglfw -lGL -lGLU -lGLEW

# Source files
SRC = src/main.cpp src/glad.c src/shape.cpp src/game.cpp src/shader.cpp src/layout.cpp

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
