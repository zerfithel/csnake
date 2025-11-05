#include <stdlib.h>
#include <ncurses.h>

#include "include/snake.h"
#include "structures.h"

// Function to create a new apple (assign 'randomly generated' x and y to it and return it)
Apple new_apple(size_t max[2]) {
  Apple apple;
  apple.x = rand() % max[0]; // Generate x
  apple.y = rand() % max[1]; // Generate y
  return apple;
}

// Function to place an apple (if its at place where player it retry)
void place_apple(Apple *apple, Snake *head) {
  do {
    apple->x = rand() % WIDTH; // Generate x
    apple->y = rand() % HEIGHT; // Generate y
  } while (is_snake_at(head, apple->x, apple->y)); // Do until its places on free spot

  return;
}

// Function to draw an apple
void draw_apple(Apple *apple) {
  mvaddch(apple->y, apple->x, APPLE_CHAR); // Draw apple character '@' at x, y coordinates
  return;
}

