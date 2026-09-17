
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#define INI_CHARS_PER_LINE 80

typedef struct {
  char *line;
  size_t size;
} TextData;

// Creating a dynamically allocatable data structure to store text data.
TextData *dynamic_text() {

  TextData *text = malloc(sizeof(TextData));

  text->line = malloc((sizeof(char)) * INI_CHARS_PER_LINE);
  text->size = INI_CHARS_PER_LINE;

  return text;
}

// Reallocate the size of data if the text size is less than dedicated size.
TextData *extend_line(TextData *text) {

  if (text->size >= INI_CHARS_PER_LINE) {

    size_t new_size = text->size * 2;

    void *temp = realloc(text->line, new_size);

    if (temp == NULL && text->size > 0) {
      perror("Error Shrinking the size of the text per line");
      return text;
    }

    text->line = temp;
    text->size = new_size;
    return text;
  }
  return text;
}

int main(void) {

  TextData *text = dynamic_text();

  text->line = "Hello this is a test to see if the data structure works";
  text->size = sizeof(text->line);

  printf("%s is the line and its size is %zu", text->line, text->size);

  free(text);
}
