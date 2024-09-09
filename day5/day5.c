#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

enum {
  STACK_SIZE = 100,
  STACKS_COUNT = 10
};

struct Stack {
  int key;
  int values[STACK_SIZE];
};

struct Stack *stacks[STACKS_COUNT];

_Bool is_valid( int value ) {
  return value >= 65 && value <= 90;
}

_Bool need_skip_line( char* line ) {
  return line[0] == '\n' || line[1] == '1';
}

int find_column( double index ) {
  static const int COLUMN_OFFSET = 4;
  int result = (int) floor(index / COLUMN_OFFSET);

  return index ? result : 0;
}

int find_index( struct Stack* stack ) {
  int index = -1;

  for (int i = 0; i <= STACK_SIZE; i++) {
    if (!stack->values[i]) {
      index = i;
      break;
    }
  }

  return index;
}

void insert( struct Stack* stack, int value ) {
  int index = find_index(stack);

  stack->values[index] = value;
}

struct Stack* lookup( int key ) {
  struct Stack* value = stacks[key];

  if (!value) {
    value = (struct Stack*) malloc(sizeof(struct Stack));
    value->key = key;

    stacks[key] = value;
  }

  return value;
}

void update_stacks( int column, int value ) {
  struct Stack* current_stack = lookup(column);

  current_stack->key = column;
  insert(current_stack, value);
}

void reorganize_stack( int source, int target, int count ) {
  struct Stack* _source = stacks[source];
  struct Stack* _target = stacks[target];

  for (int i = 0; i < count; i++) {
    for (int j = STACK_SIZE; j > 0; j--) {
      _target->values[j] = _target->values[j - 1];
      _target->values[j - 1] = 0;
    }
  }

  for (int i = 0; i < count; i++) {
    _target->values[count - 1 - i] = _source->values[i];
  }

  for (int i = 0; i < count; i++) {
    for (int j = 0; j < STACK_SIZE; j++) {
      _source->values[j] = _source->values[j + 1];
      _source->values[j + 1] = 0;
    }
  }
}

void free_table() {
  for (int i = 0; i < STACKS_COUNT; i++) {
    if (stacks[i]) free(stacks[i]);
  }
}


void print_values() {
  for (int i = 0; i <= STACKS_COUNT; i++) {
    if (stacks[i]) {
      printf("STACK KEY: %i\n", stacks[i]->key);
      printf("\t -> STACK value: %c\n", stacks[i]->values[0]);

      printf("\n\n");
    }
  }
}

int main() {
  FILE *stream;
  char *line = NULL;
  int result = 0, line_index = 0;

  size_t len = 0;

  stream = fopen("./puzzle.txt", "r");

  while (getline(&line, &len, stream) != -1) {
    if (need_skip_line(line)) continue;

    if (line[0] == 'm') {
      char cp[strnlen(line, 100)];
      strcpy(cp, line);

      int count = atoi(strtok(cp, "move "));
      int source = atoi(strtok(NULL, " from "));
      int target = atoi(strtok(NULL, " to "));

      reorganize_stack(source - 1, target - 1, count);
      continue;
    }

    for (int i = 0; i < len; i++) {
      if (line[i] && is_valid(line[i])) {
        update_stacks(find_column(i > 1 ? i : 0), line[i]);
      }
    }

    line_index++;
  }

  print_values();

  free_table();
  free(line);
  fclose(stream);

  return 0;
 }
