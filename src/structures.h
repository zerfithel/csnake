#ifndef STRUCTURES_H
#define STRUCTURES_H

#define START_SIZE 8
#define APPLE_CHAR '@'
#define SNAKE_CHAR 'O'

#define WIDTH 40
#define HEIGHT 20

enum DIRECTIONS {
  DOWN,
  UP,
  LEFT,
  RIGHT,
};

// Linked list
typedef struct Snake {
  int x; // x coordinate
  int y; // y Coordinate
  struct Snake *next; // pointer to next segment
} Snake;

typedef struct Apple {
  int x; // x coordinate
  int y; // y coordinate
} Apple;


#endif // STRUCTURES_H
