#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum result_values {
  DRAW = 3,
  WIN = 6
};

enum play_values {
  ROCK = 1,
  PAPER = 2,
  SCISSORS = 3
};

struct results {
  const char WIN;
  const char LOSE;
  const char DRAW;
};

struct moves {
  const char ROCK;
  const char PAPER;
  const char SCISSORS;
};

const int SIZE = 4;
const char *separator = " ";

int play_value(int play, struct moves moves) {
  if (moves.ROCK == play) return ROCK;
  if (moves.PAPER == play) return PAPER;
  if (moves.SCISSORS == play) return SCISSORS;

  return 0;
}

int main() {
  struct results results = { 'Z', 'X', 'Y' };
  struct moves moves = { 'A', 'B', 'C' };

  int accumulator = 0, current_play_value = 0;

  FILE *stream;
  char line[SIZE], *p_opponent_play, *p_play;

  stream = fopen("./strategy.txt", "r");

  while ((fgets(line, SIZE, stream)) != NULL) {
    if (strcmp(line, "\n") == 0) {
      accumulator += current_play_value;

      current_play_value = 0;
      continue;
    };

    p_opponent_play = strtok(line, separator);
    p_play = strtok(NULL, separator);

    int opponent_play = (int) p_opponent_play[0];
    int play = (int) p_play[0];

    if (play == results.DRAW) {
      current_play_value = play_value(opponent_play, moves) + DRAW;
      continue;
    }

    _Bool is_victory = play == results.WIN;

    if (opponent_play == moves.ROCK) current_play_value = is_victory ? PAPER + WIN : SCISSORS;
    if (opponent_play == moves.PAPER) current_play_value = is_victory ? SCISSORS + WIN : ROCK;
    if (opponent_play == moves.SCISSORS) current_play_value = is_victory ? ROCK + WIN : PAPER;
  }

  fclose(stream);

  printf("The result is: %d\n", accumulator);
}
