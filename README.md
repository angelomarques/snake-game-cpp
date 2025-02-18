# Snake Game in C++

## About the project

Snake game implemented in C++ using OpenGL and GLFW.
This project wast built to following good architecture with Data Structures and Algorithms.

<p align="center">
  <img src="./docs/presentation.gif" alt="Presentation" width="800px">
</p>

## Concepts

- [Snake Tile Data Structure](#snake-tile-data-structure)
- [Collisions Logic](#collisions-logic)

### Snake Tile Data Structure

<p align="center">
  <img src="./docs/data-structure.jpg" alt="Presentation" width="1000px">
</p>

The snake game was implemented using a doubly linked list. This data structure allows us to efficiently manage the snake's body segments and create smooth moving animations.

Each segment of the snake is represented as a node in the doubly linked list, with pointers to both the previous and next segments. This setup makes it easy to add new segments when the snake eats food and move the snake as the node takes the position of the next one.

### Collisions Logic

## How to run (Linux)

<!-- ## How to run

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./snake-game
```

## How to play

- Use the arrow keys to move the snake.
- Press the space bar to make the snake jump.
- Press the enter key to restart the game.

## How to compile and run

```bash
$ make
$ ./main
```

## How to test

```bash
$ ./snake-game
``` -->

<!-- - Linked list because we need the info of the next node -->
<!-- - The tail of the snake is the head of the linked list because it's more fast to insert the new node -->
