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

void clearScreen() {
  printf("\033[1;1H\033[2J");
  fflush(stdout);
}

int main() {

  enable_raw_mode();
  clearScreen();

  char c;

  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
    putchar(c);
    fflush(stdout);
  }

  return 0;
}
