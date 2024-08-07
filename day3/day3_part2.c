#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

enum {
  MULTIPLIER = 31,
  NHASH = 52,
  UPPERCASE_OFFSET = 38,
  LOWERCASE_OFFSET = 96
};

struct Letter {
  int letter;
  int line_count;
  int lines[3];
  struct Letter *next;
};

struct Letter *symtab[NHASH];

struct Letter* lookup(int letter, int create) {
  int h = letter;
  struct Letter *sym;

  for (sym = symtab[h]; sym != NULL; sym = sym->next) {
    if (letter == sym->letter) return sym;
  }

  if (create) {
    sym = (struct Letter *) malloc(sizeof(struct Letter));
    sym->letter = letter;
    sym->line_count = 0;
    sym->next = symtab[h];
    symtab[h] = sym;
  }

  return sym;
}

int main(void) {
  FILE *stream;
  char *line = NULL;
  int sum = 0;

  size_t len = 0;
  ssize_t read;

  stream = fopen("./puzzle.txt", "r");
  int count = 0;

  while ((read = getline(&line, &len, stream)) != -1) {
    int string_size = read - 1;

    for (int i = 0; i < string_size; i++) {
      int value = isupper(line[i]) ? (line[i] - UPPERCASE_OFFSET) : (line[i] - LOWERCASE_OFFSET);
      struct Letter *letter = NULL;

      if (count == 0) {
        letter = lookup(value, 1);
        letter->lines[count] = count;
        continue;
      }

      if ((letter = symtab[value]) != NULL) {
        int already_on_line = letter->lines[count];

        if (!already_on_line) {
          letter->lines[count] = count;
          letter->line_count++;
        }
      }
    }

    if (count == 2) {
      struct Letter *sym;

      for (int i = 0; i <= NHASH; i++) {
        if ((sym = symtab[i]) == NULL) continue;

        if (sym->line_count == 2) sum += sym->letter;

        symtab[i] = NULL;
      }

      count = 0;
    } else {
      count++;
    }
  }

  printf("RESULT: %i\n", sum);

  free(line);
  fclose(stream);
}
