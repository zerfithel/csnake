/* Simple snake game in C. Written because I was bored */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ncurses.h>

#include "include/snake.h"
#include "include/apple.h"
#include "include/game.h"
#include "structures.h"

#define reset_score() score = 0;

// Global variable that contains at which direction snake is moving
int direction = RIGHT;

int main(void) {
  srand(time(NULL)); // Send rand() seed

  initscr(); // Initialize ncurses screen
  cbreak(); // Enable cbreak mode
  noecho(); // Disable echo mode
  curs_set(0); // Disable cursor
  keypad(stdscr, TRUE); // Enable keypad
  nodelay(stdscr, TRUE); // For zero delay players

  size_t sizes[2] = { COLS, LINES }; // Table containing columns and lines of map

  Snake *snake = new_snake(START_SIZE); // Create snake
  Apple apple = new_apple(sizes); // Create apple
  unsigned int score = 0; // Score (amount of eaten apples)

  place_apple(&apple, snake); // Place one apple randomly

  // Infinite loop until player loses
play_again:
  for (;;) {
    clear(); // Clear the screen
    draw_apple(&apple); // Draw a new apple to the screen
    update_snake(snake); // Update snake new moving direction so player cant move like alien
    move_snake(snake); // Move snake coordinates (each segment)
    draw_snake(snake); // Draw whole snake

    // If snake touches apple, increase length of it and score (also place an apple)
    if (is_snake_on_apple(snake, &apple)) {
      lengthen_snake(snake);
      score++;
      place_apple(&apple, snake);
    }

    // If player loses then escape the loop
    if (is_snake_touching_itself(snake)) {
      break;
    }

    // If snake hit the border escape the loop
    if (did_snake_hit_border(snake)) {
      break;
    }

    refresh(); // Refresh the screen to view all things
    napms(300); // Sleep for 300 miliseconds
  }
  
  // After escaping the loop display game over screen
  if (game_over(score, score + START_SIZE)) {
    // game_over() returns true if user pressed ENTER (replay)
    nodelay(stdscr, TRUE); // Re enable no delay mode
    delete_snake(snake); // Remove old snake
    snake = new_snake(START_SIZE); // Create new snake
    reset_score(); // Reset score
    goto play_again; // Go to start of the loop
  }

  endwin();
  return 0;
}
