#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

struct Stack {
  int key;
  int values[26];
};

struct Stack *stacks[10];

_Bool is_valid( int value ) {
  return (value && !isspace(value) && value != '[' && value != ']');
}

int find_column( double index ) {
  static const int COLUMN_OFFSET = 3;

  return round(index / COLUMN_OFFSET);
}

void insert( struct Stack* stack, int value ) {
  for (int i = 0; i <= 26; i++) {
    if (!stack->values[i]) {
      stack->values[i] = value;
      return;
    }
  }
}

struct Stack* lookup( int key, _Bool create ) {
  struct Stack* value = stacks[key];

  if (create && value == NULL) {
    value = (struct Stack*) malloc(sizeof(struct Stack));
    value->key = key;

    stacks[key] = value;
    return value;
  }

  return value;
}

int main() {
  FILE *stream;
  char *line = NULL;
  int result = 0, line_index = 0;

  size_t len = 0;

  stream = fopen("./test.txt", "r");

  while (getline(&line, &len, stream) != -1) {
    if (line[1] == '1') continue;

    for (int i = 0; i< len; i++) {
      if (is_valid(line[i])) {
        int column;

        if (i > 1) {
          column = find_column(i) - 1;
          struct Stack* current_stack = lookup(column, true);

          current_stack->key = column;
          insert(current_stack, line[i]);
        } else {
          column = 0;
          struct Stack* current_stack = lookup(column, true);

          current_stack->key = column;
          insert(current_stack, line[i]);
        }
      }
    }

    line_index++;
  }

  for (int i = 0; i < 10; i++) {
    if (stacks[i]) {
      printf("STACK KEY: %i\n", stacks[i]->key);
      for (int j = 0; j < 10; j++) {
        printf("STACK value: %c\n", stacks[i]->values[j]);
      }

      printf("\n\n");
    }
  }

  // printf("RESULT: %i\n", result);
  free(line);
  fclose(stream);
 }
