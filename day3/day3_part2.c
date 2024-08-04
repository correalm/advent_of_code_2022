#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int const UPPERCASE_OFFSET = 38;
int  const LOWERCASE_OFFSET = 96;

enum { MULTIPLIER = 31, NHASH = 52 };

struct Letter {
  int letter;
  int count;
  struct Letter *next;
};

struct Letter *symtab[NHASH];

unsigned int hash(int letter) {
  unsigned int h = MULTIPLIER * letter;

  return h % NHASH;
}

struct Letter* lookup(int letter, int create, int value) {
  int h;
  struct Letter *sym;

  h = letter;

  for (sym = symtab[h]; sym != NULL; sym = sym->next) {
    if (letter == sym->letter) return sym;
  }

  if (create) {
    sym = (struct Letter *) malloc(sizeof(struct Letter));
    sym->letter = letter;
    sym->count = 1;
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

  stream = fopen("./test.txt", "r");
  int count = 0;

  while ((read = getline(&line, &len, stream)) != -1) {
    int string_size = read - 1;


    for (int i = 0; i <= string_size; i++) {
      struct Letter *letter = lookup(line[i], 0, count);

      if (letter == NULL) lookup(line[i], 1, 1);
      else {
        letter->count++;
        printf("LETTER COUNT: %i | LETTER: %i\n", letter->count, letter->letter);
      }
    }

    count++;

    if (count == 2) {
      // need calculate here
      // and clear the state
    }
  }

  printf("RESULT: %i\n", sum);

  free(line);
  fclose(stream);
}
