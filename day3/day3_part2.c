#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

enum {
  NHASH = 52,
  GROUP_SIZE = 3,
  UPPERCASE_OFFSET = 38,
  LOWERCASE_OFFSET = 96
};

struct Dict {
  int key;
  int lines[3];
};

struct Dict *table[NHASH];

struct Dict* lookup(int key, int create) {
  struct Dict *value = table[key];

  if (create && value == NULL) {
    value = (struct Dict*) malloc(sizeof(struct Dict));
    value->key = key;
    table[key] = value;
  }

  return value;
}

_Bool present_in_all_lines(struct Dict* value) {
  int result = 0;

  for (int i = 0; i < GROUP_SIZE; i++) {
    result += value->lines[i];
  }

  return result == GROUP_SIZE;
}

void reset_value(struct Dict* value) {
  for (int i = 0; i < GROUP_SIZE; i++) {
    value->lines[i] = 0;
  }
}

void free_table() {
  for (int i = 0; i <= NHASH; i++) {
    if (table[i] != NULL) free(table[i]);
  }
}

int main(void) {
  FILE *stream;
  char *line = NULL;
  int sum = 0, count = 0;

  size_t len = 0;
  ssize_t read;

  stream = fopen("./puzzle.txt", "r");

  while ((read = getline(&line, &len, stream)) != -1) {
    int string_size = read - 1;

    for (int i = 0; i < string_size; i++) {
      int key = isupper(line[i]) ? (line[i] - UPPERCASE_OFFSET) : (line[i] - LOWERCASE_OFFSET);

      struct Dict* value = lookup(key, 1);
      value->lines[count] = 1;
    }

    if (count == GROUP_SIZE - 1) {
      struct Dict* value;

      for (int i = 0; i <= NHASH; i++) {
        if ((value = table[i]) != NULL) {
          if (present_in_all_lines(value)) sum += value->key;

          reset_value(value);
        }
      }

      count = 0;
    } else {
      count++;
    }
  }

  printf("RESULT: %i\n", sum);

  free_table();
  free(line);
  fclose(stream);
}
