#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const int MAX_LEN = 100;

struct Elve {
  int calories;
  struct Elve *next;
};

struct Elve *new_item(int calories) {
  struct Elve *new_elve;

  new_elve = (struct Elve *) malloc(sizeof(struct Elve));

  new_elve->calories = calories;
  new_elve->next = NULL;

  return new_elve;
}

struct Elve *add(struct Elve *listp, struct Elve *new_elve) {
  new_elve->next = listp;
  return new_elve;
}

struct Elve *insert_ascending(struct Elve *listp, struct Elve *new_elve) {
  if (listp == NULL || new_elve->calories > listp->calories) {
    return add(listp, new_elve);
  }

  struct Elve *head = listp;

  for (; head->next != NULL; head = head->next) {
    if (head->calories > new_elve->calories && head->next->calories < new_elve->calories) {
      new_elve->next = head->next;
      break;;
    }
  }

  head->next = new_elve;
  return listp;
}

int main() {
  struct Elve *elves = NULL;

  FILE *stream;
  char line[MAX_LEN], *result;
  int tracker, sum = 0;

  stream = fopen("./food.txt", "r");

  while ((result = fgets(line, MAX_LEN, stream)) != NULL) {
    if (strcmp(result, "\n") == 0) {
      elves = insert_ascending(elves, new_item(tracker));
      tracker = 0;
    } else {
      tracker += atoi(result);
    }
  }

  elves = insert_ascending(elves, new_item(tracker));
  for (int i = 0; i < 3; i++) {
    sum += elves->calories;
    elves = elves->next;
  }

  printf("The sum is: [%i]\n", sum);

  if (fclose(stream)) {
    perror("Error on close file");
  }

  return 0;
}
