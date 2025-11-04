#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>

#include "structures.h"

// Function to create a new snake
// segments - how long the snake should be
Snake *new_snake(unsigned int segments) {
  if (segments == 0) return NULL; // No segments to create
  
  Snake *head = malloc(sizeof(Snake)); // Create new structures
  
  /* Default x, y and direction */
  head->x = 0;
  head->y = 0;
  head->direction = RIGHT;
  head->next = new_snake(segments - 1); // Recursive call to create another segment

  return head; // Return head of created snake
}

// Function to update snake moving direction
void update_snake(Snake *head) {
  int c = getch(); // Get character input from user (without ENTER having to be pressed)

  switch(c) {
    case KEY_DOWN: // arrow down = moving down, same applies to bottom cases
      if (head->direction != UP) {
        head->direction = DOWN;
      }
      break;
    case KEY_UP:
      if (head->direction != DOWN) {
        head->direction = UP;
      }
      break;
    case KEY_LEFT:
      if (head->direction != RIGHT) {
        head->direction = LEFT;
      }
      break;
    case KEY_RIGHT:
      if (head->direction != LEFT) {
        head->direction = RIGHT;
      }
      break;
  }
}

// Function to add a new segment to the snake
void lengthen_snake(Snake *head) {
  // Recursive call to find last element of snake
  if (head->next != NULL) { 
    lengthen_snake(head->next);
    return;
  }

  /* Create new segment and assign values to it (x, y, direction) */
  head->next = malloc(sizeof(Snake));
  head->next->x = head->x;
  head->next->y = head->y;
  head->next->direction = head->direction;

  return;
}

// Function to draw whole snake to the screen
void draw_snake(Snake *head) {
  Snake *current = head; // variable that will point to one segment
  
  while (current != NULL) { // Iterate until next is pointing to NULL (it means that its last segment of linked list)
    mvaddch(current->y, current->x, SNAKE_CHAR); // Print snake char 'O' at x and y coordinate
    current = current->next; // Move to next segment
  }

  refresh(); // Refresh ncurses screen
  return;
}

// Function to check if snake is on same coordinates as apple
bool is_snake_on_apple(Snake *s, Apple *a) {
  // Returns true if 's' (snake) x and y is same as 'a' (apple) coordinates
  return (s->x == a->x && s->y == a->y);
}

// Function to move snake x and y
void move_snake(Snake *head) {
  /* Save previous x and y coordinate */
  int prev_x = head->x;
  int prev_y = head->y;

  switch(head->direction) {
    case DOWN:
      head->y++; // If moving down increase y (it looks weird but thats just how ncurses work idk). Same applies to cases below
      break;
    case UP:
      head->y--;
      break;
    case LEFT:
      head->x--;
      break;
    case RIGHT:
      head->x++;
      break;
  }

  Snake *current = head->next; // Another 'current' variable
  // While loop that will end at last segment
  while (current != NULL) {
    /* Temporary variables to save both x and y of current segment */
    int temp_x = current->x;
    int temp_y = current->y;
    
    /* Move snake segment to previous (segment that was before) coordinates */
    current->x = prev_x;
    current->y = prev_y;

    prev_x = temp_x;
    prev_y = temp_y;

    current = current->next; // Go to next segment
  }
}

// Function to check if any of snakes segments is at x, y
bool is_snake_at(Snake *head, int x, int y) {
  Snake *current = head; // Current variable
  // Iterate on all segments
  while (current != NULL) {
    // Return true if current segment is at given coordinates
    if (current->x == x && current->y == y) {
      return true;
    }

    current = current->next; // Move to the next segment
  }

  return false; // If loop ended it means no matches were found
}

// Function to check if snake is colliding with other segment (this means loose)
bool is_snake_touching_itself(Snake *head) {
  if (head == NULL) return false; // Empty snake
  
  /* Save head x and y */
  int head_x = head->x;
  int head_y = head->y;

  Snake *current = head->next; // Start from the segment after the head
  while (current != NULL) {
    // If head is touching any segment after it return true (lose)
    if (head_x == current->x && head->y == current->y) {
      return true;
    }

    current = current->next; // Move to next segment
  }

  // If loop was escaped, game still continues
  return false;
}
