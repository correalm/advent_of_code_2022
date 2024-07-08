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

// struct Elve *add_front(struct Elve *listp, struct Elve *new_elve) {
//   new_elve->next = listp;
//   return new_elve;
// }

struct Elve *add_front(struct Elve *listp, struct Elve *new_elve) {
  if (listp == NULL) {
    new_elve->next = listp;
    return new_elve;
  } else {
    if (new_elve->calories < listp->calories) {

      new_elve->next = listp;
      return new_elve;
    } else {
      struct Elve *head = listp;

      for (; head->next != NULL; head = head->next) {
        if (head->calories < new_elve->calories && head->next->calories > new_elve->calories) {
          new_elve->next = head->next;
          head->next = new_elve;
          break;;
        }
      }

      if (head->next == NULL) {
        head->next = new_elve;
      }
      return listp;
    }
  }
}

int main() {
  struct Elve *elves = NULL;

  FILE *file;
  char line[MAX_LEN], *result;

  struct CalorieRanking {
    int first;
    int second;
    int third;

    int tracker;
  };

  struct CalorieRanking foo = { 0, 0, 0, 0 };

  file = fopen("./test.txt", "r");

  while ((result = fgets(line, MAX_LEN, file)) != NULL) {
    if (strcmp(result, "\n") == 0) {
      elves = add_front(elves, new_item(foo.tracker));

      foo.tracker = 0;
    } else {
      foo.tracker += atoi(result);
    }
  }

  elves = add_front(elves, new_item(foo.tracker));
  // printf("VALUE before loop IS: %d\n", elves->calories);
  while (elves != NULL) {
    printf("VALUE IS: %d\n", elves->calories);
    elves = elves->next;
  }

  // printf("FIRST: counter[%i]\n", foo.first);
  // printf("SECOND: counter[%i]\n", foo.second);
  // printf("THIRD: counter[%i]\n", foo.third);

  // printf("FOO IS: counter[%i]\n", foo.first + foo.second + foo.third);

  if (fclose(file)) {
    perror("Error on close file");
  }

  return 0;
}
