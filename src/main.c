#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios original_term;

void dis_raw_mode() { tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_term); }

void enable_raw_mode() {
  tcgetattr(STDIN_FILENO, &original_term);
  atexit(dis_raw_mode);

  struct termios raw = original_term;

  cfmakeraw(&raw);

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

/*
All the print statements with numbers and escape codes are used from the ASCII
Escape sequence provided by the
https://www.gnu.org/software/screen/manual/html_node/Control-Sequences.html feel
free to use it as a refrence to know what is going on if confused.
*/

void clearScreen() {
  printf("\033[1;1H\033[2J");
  fflush(stdout);
}

void printSideLines() {
  for (int i = 0; i < 1000; i++) {
    printf("~ \x1b[E");
  }
  printf("\x1b[H");
  fflush(stdout);
}

void moveCursor(char c) {
  switch (c) {
  case 'h':
    printf("\x1b[D");
    break;
  case 'j':
    printf("\x1b[B");
    break;
  case 'k':
    printf("\x1b[A");
    break;
  case 'l':
    printf("\x1b[C");
    break;
  }
}

int main() {
  enable_raw_mode();
  clearScreen();
  printSideLines();

  char c;

  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
    moveCursor(c);
    putchar(c);
    fflush(stdout);
  }

  return 0;
}
