#ifndef TEXTH
#define TEXTH

#define INI_CHARS_PER_LINE 80
#include <stddef.h>

typedef struct {
  char *line;
  size_t size;
  size_t capacity;
} LineData;

typedef struct {
  LineData *lines;
  size_t size;
  size_t capacity;
} Arr_Lines;

LineData *initializing_text();
void extend_line(LineData *text);
void enterText(LineData *text, char c);

#endif
