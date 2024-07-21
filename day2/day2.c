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

const int MOVE_COUNT = 3;
int const VALUES[] = { ROCK, PAPER, SCISSORS };

char opponent_moves[] = { 'A', 'B', 'C' };
char moves[] = { 'X', 'Y', 'Z' };

const int SIZE = 4;
const char *separator = " ";

_Bool player_wins(int player_move, int opponent_move) {
  int result = opponent_move - player_move;
  return result == 2 || result == -1;
}

_Bool is_draw(int player_move, int opponent_move) {
  return (player_move - opponent_move) == 0;
}

int play_value(int play, char *moves) {
  for (int i = 0; i < MOVE_COUNT; i++) {
    if (play == moves[i]) return VALUES[i];
  }

  return 0;
}

int main() {
  int accumulator = 0;
  int current_game = 0;

  FILE *stream;
  char line[SIZE], *p_opponent_play, *p_play;

  stream = fopen("./strategy.txt", "r");

  while ((fgets(line, SIZE, stream)) != NULL) {
    if (strcmp(line, "\n") == 0) {
      accumulator += current_game;

      current_game = 0;
      continue;
    };

    p_opponent_play = strtok(line, separator);
    p_play = strtok(NULL, separator);

    int opponent_play = (int) p_opponent_play[0];
    int play = (int) p_play[0];

    int opponent_play_value = play_value(opponent_play, opponent_moves);
    current_game = play_value(play, moves);

    if (is_draw(current_game, opponent_play_value)) {
      current_game += DRAW;
      continue;
    }

    if (player_wins(current_game, opponent_play_value)) { current_game += WIN; }
  }

  fclose(stream);

  printf("The result is: %d\n", accumulator);
}
