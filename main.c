/* Simple snake game in C. Written because I was bored */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ncurses.h>

#include "include/snake.h"
#include "include/apple.h"
#include "structures.h"

int main(void) {
  initscr(); // Initialize ncurses screen
  cbreak(); // Enable cbreak mode
  noecho(); // Disable echo mode
  curs_set(0); // Disable cursor
  keypad(stdscr, TRUE); // Enable keypad
  nodelay(stdscr, TRUE); // For zero delay players

  int table[2] = { COLS, LINES }; // Table containing columns and lines of map

  Snake *snake = new_snake(START_SIZE); // Create snake
  Apple apple = new_apple(table); // Create apple
  unsigned int length = 0; // Length of snake - START_SIZE

  place_apple(&apple, snake); // Place one apple randomly

  // Infinite loop until player loses
  for (;;) {
    clear(); // Clear the screen
    draw_apple(&apple); // Draw a new apple to the screen
    update_snake(snake); // Update snake new moving direction so player cant move like alien
    move_snake(snake); // Move snake coordinates (each segment)
    draw_snake(snake); // Draw whole snake

    // If snake touches apple, increase length of it and score (also place an apple)
    if (is_snake_on_apple(snake, &apple)) {
      lengthen_snake(snake);
      length += 1;
      place_apple(&apple, snake);
    }

    // If player loses then escape the loop
    if (is_snake_touching_itself(snake)) {
      break;
    }

    refresh(); // Refresh the screen to view all things
    napms(300); // Sleep for 300 miliseconds
  }
  
  // After escaping the loop close the ncurses window and print score
  endwin();
  printf("You lose!\nscore: %d\nlength: %d\n", length + START_SIZE, length);
  return 0;
}
