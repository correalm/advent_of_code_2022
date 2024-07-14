#include <stdio.h>
#include <string.h>

enum Values {
  ROCK = 1,
  PAPER = 2,
  SCISSORS = 3
};

const int SIZE = 4;
const char *separator = " ";

int main() {
  int count = 0;
  FILE *stream;
  char line[SIZE], *token;

  stream = fopen("./test.txt", "r");

  while ((fgets(line, SIZE, stream)) != NULL) {
    if (strcmp(line, "\n") == 0) {
      printf("calculate the value...\n");
      printf("should update the value of count\n");

      continue;
    };

    token = strtok(line, separator);

    printf("LINE IS: %s\n", line);
    while (token != NULL) {
      printf("TOKEN IS: %s\n", token);
      token = strtok(NULL, separator);
    }
  }
}
