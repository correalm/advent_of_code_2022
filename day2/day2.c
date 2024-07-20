#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum game_values {
  LOST = 0,
  DRAW = 3,
  WIN = 6
};

enum game {
  ROCK = 1,
  PAPER = 2,
  SCISSORS = 3
};

char opponent_moves[] = { 'A', 'B', 'C' };
char moves[] = { 'X', 'Y', 'Z' };
int values[] = { ROCK, PAPER, SCISSORS };

const int SIZE = 4;
const char *separator = " ";

int main() {
  int accumulator = 0;
  int opponent_count = 0;
  int count = 0;

  FILE *stream;
  char line[SIZE], *token, *token_test;

  stream = fopen("./strategy.txt", "r");

  while ((fgets(line, SIZE, stream)) != NULL) {
    if (strcmp(line, "\n") == 0) {
      accumulator += count;

      opponent_count = 0;
      count = 0;
      continue;
    };

    token = strtok(line, separator);
    token_test = strtok(NULL, separator);

    int opponent = (int) token[0];
    int current_game = (int) token_test[0];

    for (int i = 0; i < 3; i++) {
      if (opponent == opponent_moves[i]) {
        opponent_count += values[i];
      }
    }

    for (int i = 0; i < 3; i++) {
      if (current_game == moves[i]) {
        count += values[i];
      }
    }

    if ((opponent_count - count) == 2 || (opponent_count - count) == -1) {
      count += WIN;
    } else if ((opponent_count - count) == 1 || (opponent_count - count) == -2) {
      opponent_count += WIN;
    } else {
      count += DRAW;
    }
  }

  printf("The result is: %d\n", accumulator);
}
