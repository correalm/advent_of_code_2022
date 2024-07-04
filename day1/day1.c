#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const int MAX_LEN = 100;

int main() {
  FILE *file;
  char line[MAX_LEN], *result;

  int current_index = 0;

  struct Foo {
    int index;
    int counter;
    int tracker;
  };

  struct Foo foo = { 0, 0, 0 };

  file = fopen("./food.txt", "r");

  while ((result = fgets(line, MAX_LEN, file)) != NULL) {
    if (strcmp(result, "\n") == 0) {
      if (foo.tracker == foo.counter) {
        foo.index = current_index;
      }

      current_index++;
      foo.tracker = 0;
    } else {
      foo.tracker += atoi(result);
      if (foo.tracker > foo.counter) {
        foo.counter = foo.tracker;
      }
    }
  }

  printf("FOO IS: counter[%i] | index[%i]\n", foo.counter, foo.index);

  if (fclose(file)) {
    perror("Error on close file");
  }

  return 0;
}
