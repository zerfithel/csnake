#ifndef APPLE_H
#define APPLE_H

// Function to create a new apple
Apple new_apple(size_t max[2]);

// Function to place a new apple on the map
void place_apple(Apple *apple, Snake *head, size_t max[2]);

// Function to draw the apple on the map (reads apple x & y coordinates)
void draw_apple(Apple *apple);

#endif // APPLE_H
