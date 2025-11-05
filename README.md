# 🐍 CSnake - Snake game in C

**Csnake** is a yet another implementation of Snake game in C-Lang. CSnake is capable of spawning new apples, increasing the length of snake after eating one and if snakes head collides with other snake segment it exits the game and prints score & length of your snake.

---

# 🐍 How does the game work under the hood

### Snake structure

**CSnake** uses a `linked list` in order to save all required data about every snakes segment. The data structures looks in the code like this:

```C
typedef struct Snake {
    int x; // x coordinate of segment
    int y; // y coordinate of segment
    int direction; // direction where snake is moving
    struct Snake *next; // pointer to the next 'clone' of this structure, if it points to NULL it means we are at last segment
} Snake;
```

### Apple structure

```C
typedef struct Apple {
    int x; // x coordinate of apple
    int y; // y coordinate of apple
} Apple;
```

The `linked list` structure is explained here: [wikipedia.org/wiki/Linked_list](https://en.wikipedia.org/wiki/Linked_list).

---

### Main function (main.c)

First inside the `main()` function a new snake is being created with the `new_snake(n)` function which creates a new snake with n-segments and returns it. Then it creates a new apple structure using `new_apple(table)` where table is an array of both columns and lines of the map. The `place_apple()` function updates the apple structures by 'randomizing' x and y coordinate for apple, then it checks if snake is already at these coordinates with `is_snake_at(Snake *s, int x, int y)` function. If this function returns true (snake is there) then it regenerates the apple until it finds an empty place. The `place_apple()` function just places the apple by updating the apple structure but it doesnt draw it and thats where `draw_apple(Apple *a)` function comes into, it takes an apple structure and draws and apple at x and y coordinate defined in the apple structure `a`. Snake moving mechanism is implemented in `update_snake(Snake *s)` function that will wait for user to click an arrow key and depending on the key it will set an moving direction inside a snake structure (up arrow = moving up, left = moving left etc.). Next the `move_snake(Snake *s)` function is called that will read moving direction that was set with `update_snake(Snake *s)` and will either increaseor decrease the `x` or `y` coordinate (depending on the moving direction) of the head. Inside a `while` loop it will iterate on all segments and move these to previous location of previous segment that was moved. Then `draw_snake(Snake *head)` is called which will iterate with `while` loop on every snake segment and print snake character `O` at x and y saved inside at segment. If it reaches an segment where pointer to next segment points to `NULL` then it knows this is last segment and will draw last segment and quit. In every loop it also checks by using `is_snake_on_apple(Snake *s, Apple *a)` function to determine if snakes head x and y coordinate is same as apples coordinate and if yes it returns true. Inside the main loop it calls the `lengthen_snake(Snake *head)` function to add a new segment at the end of the snake.

### File explanation

- **`snake.c`** → File that contains functions to manipulate the snake, gather information about it, draw it, move etc.

- **`apple.c`** → File that contains functions to generate a new apple, place it and draw on the screen.

- **`main.c`** → File with `main()` function with which the program starts. It contains an infinite loop that will invoke functions from both `snake.c` and `apple.c` to gather user input and manipulate the snake.

- **`structures.h`** - Header file that contains macros, enums and structures used for the project (snake structure, apple structure).

- **`include/*.h`** - Header files that declare functions from `snake.c` and `apple.c` so they can be used in the `main.c`.

---

### Iterating on Snake structure

Because `Snake` structure is a linked list to get to the last segment of snake we gotta iterate on it until the `next` pointer points to NULL (and not a other instantion of that structure). There are two ways to iterate on linked list that were used in code.

- **Iteration**
```C
Snake *current = head;

while (current->next != NULL) { // Iterate until the `next` pointer points to NULL (it means that this is last segment)
    printf("x: %d\ny: %d\n", current->x, current->y); // Print x and y coordinate
    
    current = current->next; // Go over to the next segment
}
```

- **Recursion**
```C
void recursive_method(Snake *s) {
    printf("x: %d\ny: %d\n", s->x, s->y); // Print the x and y coordinate
    recursive_method(s->next); // Call the function recursively but with the 's' as a pointer to next structure
    return; // After rolling back after the recursive call, return to the code where function was invoked (return in void functions are not necessary but it improves readability imo)
}
```

---

### Project functions explained 

`snake.c`:

- **`Snake *new_snake(unsigned int segments)`** - Creates a new snake with n-segments and returns it to the caller.

- **`void update_snake(Snake *head)`** - Function that waits for user to click an arrow key and depending on the arrow key it changes the snake moving direction inside snake structure (head) (up arrow = moving up etc.).

- **`void lengthen_snake(Snake *head)`** - Function to add a new segment at the end of the snake and assign x, y and direction same as oldest last segment.

- **`void draw_snake(Snake *head)`** - Iterates on each segment of snake and prints snake character `O` at x and y coordinate saved in structure for each segment.

- **`bool is_snake_on_apple(Snake *s, Apple *a)`** - Function to check if head of the snake is on same x and y as apple, if yes it will return `true`.

- **`void move_snake(Snake *head)`** - Function that saves head x and y and then based on snake moving direction updated by `update_snake()` it increases or decreases the x or y coordinate, then it iterates on each segment and assigns the x and y value same as the previous segment to make it move fully and not just the head.

- **`bool is_snake_at(Snake *head, int x, int y)`** - Function to check if any of the segments of the snake is at given x and y coordinate. Returns `true` if yes.

- **`bool is_snake_touching_itself(Snake *head)`** - Function that returns `true` if snakes head is on same x and y as any other segment (it means snake collided and player lost).

`apple.c`:

- **`Apple *new_apple(int max[2])`** - Function that returns a new apple structure with x and y generated using `rand() % max[0]` to generate x and `rand() % max[1]` to generate y.

- **`void place_apple(Apple *apple, Snake *head)`** - Function to place an apple. It generates x and y coordinate until its on empty slot. If it was generated on player it retries.

- **`void draw_apple(Apple *apple)`** - Function to draw an apple at given apple x and y coordinate.

### Ncurses functions explained used in project

- **`initscr()`** - Initializes ncurses screen.
- **`cbreak()`** - Enables cbreak mode.
- **`noecho()`** - Disables echo mode (no characters will be printed if user types characters).
- **`curs_set(0)`** - Disable cursor.
- **`keypad(stdscr, TRUE)`** - Enable keypad (arrows keys) on default screen.
- **`nodelay(stdscr, TRUE)`** - Causes `getch()` to be a non-blocking call
- **`clear()`** - Clears the screen.
- **`refresh()`** - Draw new characters (`printw()` etc. write on virtual screen and this functions draws it on screen user can see).
- **`napms(ms)`** - Take a nap (sleep) for 300 miliseconds.
- **`endwin()`** - Destroy the ncurses window.

---

# 🏓 How to play this masterpiece?

This masterpiece uses `ncurses` lib as this is the only lib I know to make TUI which doesnt by default support Windows so it might be hard to run it on Microsoft OS. It should work on all Linux distros, BSD and other Unix/Unix-like systems.

In order to play the game please make sure you have `git`, `gcc` and `ncurses, ncurses-devel` installed.

1. Clone the repository and cd into it:
```bash
git clone https://github.com/zerfithel/csnake
cd csnake/src
gcc *.c -I include -l ncurses -o csnake
sudo mv csnake /usr/bin
csnake # run the game
```

---

# 📋 Plans to add

I plan to add game ending when player leaves the map (currently it just escapes the map and you cant see the snake until you return) and some things like fake apples that are very similar to normal apples but cause random debuff like reversed moving for a while. To optimize the code I also plan to remove recursion and replace it all with iteration methods. Also I will remove `int direction` from snake structure because its dumb way to save snake direction (because its saved in each segment even though you only have to save it for head of the snake).

# ✅ About the project

The first prototype of the game was written in around `15 minutes`. After it I had to fix problems like player moving into itself and disappearing (because when you were moving right you could start moving left but I have no idea why the snake disappeared and never appeared again after this happening). Feel free to read the source. The snake game seems to be hard (especially the snake moving or growing) but its actually easy if you know how to use `linked list` structures. If you are beginning your journey with C a Snake game can be very useful to learn how to use `linked lists` and how to use a library to draw the map (or you can write your own but it will take a while). 
