#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

enum {
  NHASH = 52,
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

int validate_value (struct Dict* value) {
  int result = 0;

  result += value->lines[0];
  result += value->lines[1];
  result += value->lines[2];

  return result == 6 ? 1 : 0;
}

void reset_value (struct Dict* value) {
  value->lines[0] = 0;
  value->lines[1] = 0;
  value->lines[2] = 0;
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
      // validate only with booleans
      value->lines[count] = count + 1;
    }

    if (count >= 2) {
      struct Dict* value;

      for (int i = 0; i <= NHASH; i++) {
        value = table[i];

        if (value != NULL) {
          int need_count = validate_value(value);

          if (need_count) sum += value->key;

          reset_value(value);
        }
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
