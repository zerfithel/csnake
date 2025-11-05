#include <ncurses.h>
#include <string.h>
#include <stdbool.h>

bool game_over(unsigned int score, unsigned int length) {
  nodelay(stdscr, FALSE); // Disable no delay mode to wait for user to press ENTER or something else
  clear(); // Clear screen

  // Save max y and max x
  int max_y, max_x;
  getmaxyx(stdscr, max_y, max_x);

  int start_y = (max_y) / 2; // Middle y
  
  // Calculate length of text "Score: <score>" and print
  int len = snprintf(NULL, 0, "Score: %d", score);
  mvprintw(start_y + 1, (max_x - len) / 2, "Score: %d", score);

  // Calculate length of text "Score: <length>" and print
  len = snprintf(NULL, 0, "Length: %d", length);
  mvprintw(start_y + 2, (max_x - len) / 2, "Length: %d", length);

  // Print
  mvprintw(start_y + 3, (max_x - 36) / 2, "Press ENTER to restart or Q to quit");
  
  refresh(); // Refresh the screen
  napms(500); // Wait for 500 miliseconds before allowing user to press character (because sometimes when you die you can acidentally restart or quit if you dont want to)
  int c = 0;

  do {
    c = getch(); // Wait for user input

    // If user pressed ENTER restart the game and if pressed q/Q then quit the game
    if (c == KEY_ENTER || c == '\n') {
      return true; // Restart game
    } else if (c == 'q' || c == 'Q') {
      return false; // Quit game
    }
  } while (1);
    
}
