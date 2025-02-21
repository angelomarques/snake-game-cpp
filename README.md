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


The collision logic is designed to detect when the snake's head collides with certain elements on the grid. This is achieved by calculating the specific grid position (using the x and y coordinates) of the snake's head and comparing it with the positions of other elements such as the border, apples, and other parts of the snake's body. Here are the key steps involved:

1. Calculate Grid Position: Determine the grid position of the snake's head based on its x and y coordinates.
2. Check Self-Collision: Compare the grid position of the snake's head with the positions of the other tiles that make up the snake's body. If they match, a collision with itself is detected, which results in the game ending.
3. Check Border Collision: Compare the grid position of the snake's head with the positions of the grid's borders. If they match, a collision with the border is detected, which also results in the game ending.
4. Check Apple Collision: Compare the grid position of the snake's head with the position of the apple. If they match, a collision with the apple is detected, which typically results in the snake growing longer and the apple being repositioned.

This logic ensures that the game can accurately detect and respond to collisions, maintaining the game's rules and providing a consistent gameplay experience.

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
