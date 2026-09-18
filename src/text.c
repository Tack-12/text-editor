#include "text.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

LineData *initializing_text()
{

  LineData *text = malloc(sizeof(LineData));

  text->line = malloc((sizeof(char)) * INI_CHARS_PER_LINE);
  text->size = 0;
  text->capacity = INI_CHARS_PER_LINE;

  return text;
}

// Reallocate the size of data if the text size is less than dedicated size.
void extend_line(LineData *text)
{

  size_t new_cap = text->capacity * 2;
  void *temp = realloc(text->line, new_cap);

  if (temp == NULL && text->size > 0)
  {
    perror("Error Shrinking the size of the text per line");
  }

  text->line = temp;
  text->capacity = new_cap;
}

void enterText(LineData *text, char c)
{

  if (text->size >= text->capacity)
  {
    extend_line(text);
  }

  // Add to the end of the array of lines and increase the size of the array
  // after.
  if (c != '\n' && c != EOF)
  {
    text->line[text->size] = c;
    text->size++;
  }
}

Arr_Lines *CreateLines()
{
  const int amountofLines = 1000;
  Arr_Lines *full_text = malloc(sizeof(Arr_Lines) * amountofLines);

  if (full_text == NULL)
  {
    perror("Error Creating the Full Text");
  }

  for (int i = 0; i < amountofLines; i++)
  {
    full_text[i].lines = initializing_text();
    full_text[i].capacity = INI_CHARS_PER_LINE;
    full_text[i].size = 0;
  }
  return full_text;
}

int main(void)
{

  Arr_Lines *full_text = CreateLines();
  char c;
  int currText = 0;

  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q')
  {

    if (c == '\n')
    {
      enterText(full_text[currText].lines, '\0');
      full_text->size++;
      currText++;
    }
    else
    {
      enterText(full_text[currText].lines, c);
    }
  }

  printf("%s ; %zu ; %zu", full_text[0].lines->line, full_text[0].lines->size,
         full_text[0].lines->capacity);

  for (int i = 0; i <= full_text->size; i++)
  {
    printf("%s ; %zu ; %zu", full_text[i].lines->line, full_text[i].lines->size,
           full_text[i].lines->capacity);

    free(full_text[i].lines->line);
    free(full_text[i].lines);
  }

  free(full_text);
}
