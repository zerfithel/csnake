#ifndef SNAKE_H
#define SNAKE_H

#include "../structures.h"

// Function to create a new snake with n segments
Snake *new_snake(unsigned int segments);

// Function to update snake moving direction
void update_snake(Snake *head);

// Function to add a new segment to snake and assign x and y to it
void lengthen_snake(Snake *head);

// Function to draw snake segments
void draw_snake(Snake *head);

// Function to move snake (change x & y values in each segment)
void move_snake(Snake *head);

// Function to check if snake is on apple
bool is_snake_on_apple(Snake *s, Apple *a);

// Function to check if snake is at given coordinates
bool is_snake_at(Snake *head, int x, int y);

// Function to check if snake is touching itself (if yes then end the game obviosuly)
bool is_snake_touching_itself(Snake *head);

// Function to free whole memory that snake segments are using
void delete_snake(Snake *head);

// Function that returns true if snake head hits the border
bool did_snake_hit_border(Snake *head);

#endif // SNAKE_H
