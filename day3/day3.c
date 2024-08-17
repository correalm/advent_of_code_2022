#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int const UPPERCASE_OFFSET = 38;
int const LOWERCASE_OFFSET = 96;

struct Node {
  int value;
  struct Node *next;
};

struct Node *new_node(int value) {
  struct Node *new_node;

  new_node = malloc(sizeof(struct Node));

  new_node->value = value;
  new_node->next = NULL;

  return new_node;
}

struct Node *insert(struct Node *listp, struct Node *new_node) {
  new_node->next = listp;
  return new_node;
}

int has_value(struct Node *listp, int value) {
  if (!listp) return 0;

  struct Node *head = listp;

  do {
    if (value == head->value) return head->value;
  } while (head->next != NULL);

  return 0;
}

void free_list(struct Node *listp) {
  struct Node *next;

  for (; listp != NULL; listp = next) {
    next = listp->next;

    free(listp);
  }
}

int main() {
  struct Node *values = NULL;

  FILE *stream;
  char *line = NULL;
  int sum = 0;

  size_t len = 0;
  ssize_t read;

  stream = fopen("./puzzle.txt", "r");

  while ((read = getline(&line, &len, stream)) != -1) {
    int string_size = read - 1;
    int mid = (string_size / 2) - 1;

    for (int i = 0; i <= mid; i++) {
      for (int j = mid + 1; j <= string_size; j++) {
        if (line[i] == line[j] && !has_value(values, line[i])) {
          int value = 0;

          if (isupper(line[i])) value = line[i] - UPPERCASE_OFFSET;
          else value = line[i] - LOWERCASE_OFFSET;

          values = insert(values, new_node(line[i]));
          sum += value;
        }
      }
    }

    free_list(values);
    values = NULL;
  }

  printf("RESULT: %i\n", sum);

  free(line);
  fclose(stream);
}
