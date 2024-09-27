# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++17

# Libraries
LIBS = -lglfw -lGL -lGLU

# Source files
SRC = src/main.cpp src/shape.cpp

# Output binary
OUT = main

# Build the project
all: $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC) $(LIBS)

# Clean the build
clean:
	rm -f $(OUT)
