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

struct Game {
  const char WIN;
  const char LOSE;
  const char DRAW;
};

struct Moves {
  const char ROCK;
  const char PAPER;
  const char SCISSORS;
};

const int MOVE_COUNT = 3;
int const VALUES[] = { ROCK, PAPER, SCISSORS };

char opponent_moves[] = { 'A', 'B', 'C' };

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
  struct Game game = { 'Z', 'X', 'Y' };
  struct Moves moves = { 'A', 'B', 'C' };

  int accumulator = 0, current_game = 0;

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

    if (play == game.DRAW) {
      current_game = play_value(opponent_play, opponent_moves);
      current_game += DRAW;
      continue;
    }

    if (opponent_play == moves.ROCK) {
      if (play == game.LOSE) {
        current_game += SCISSORS;
      } else {
        current_game += PAPER;
        current_game += WIN;
      }
    }

    if (opponent_play == moves.PAPER) {
      if (play == game.LOSE) {
        current_game += ROCK;
      } else {
        current_game += SCISSORS;
        current_game += WIN;
      }
    }

    if (opponent_play == moves.SCISSORS) {
      if (play == game.LOSE) {
        current_game += PAPER;
      } else {
        current_game += ROCK;
        current_game += WIN;
      }
    }
  }

  fclose(stream);

  printf("The result is: %d\n", accumulator);
}
