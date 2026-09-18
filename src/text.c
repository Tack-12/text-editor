#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define INI_CHARS_PER_LINE 80

typedef struct {
  char *line;
  size_t size;
  size_t capacity;
} TextData;

// Creating a dynamically allocatable data structure to store text data.
TextData *dynamic_text() {

  TextData *text = malloc(sizeof(TextData));

  text->line = malloc((sizeof(char)) * INI_CHARS_PER_LINE);
  text->size = 0;
  text->capacity = INI_CHARS_PER_LINE;

  return text;
}

// Reallocate the size of data if the text size is less than dedicated size.
void extend_line(TextData *text) {

  size_t new_cap = text->capacity * 2;
  void *temp = realloc(text->line, new_cap);

  if (temp == NULL && text->size > 0) {
    perror("Error Shrinking the size of the text per line");
  }

  text->line = temp;
  text->capacity = new_cap;
}

void enterText(TextData *text, char c) {

  if (text->size >= text->capacity) {
    extend_line(text);
  }

  if (c != '\n' && c != EOF) {
    text->line[text->size] = c;
    text->size++;
  }
}

int main(void) {

  TextData *text = dynamic_text();
  char c;

  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
    enterText(text, c);
  }
  printf("%s is the line and its size is %zu ; however its capacity is %zu",
         text->line, text->size, text->capacity);
  free(text);
}
