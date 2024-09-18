#include "day6.h"
#include <time.h>
#include <stdio.h>

int main( void ) {
  clock_t start, end;
  double cpu_time_used;

  start = clock();
  int result = day6("./unity/puzzle.txt", 1);
  end = clock();

  double time_taken = (((double) (end - start)) / CLOCKS_PER_SEC) * 1000;

  printf("RESULT PART 1: %i\n", result);
  printf("TIME PART 1: %f ms\n", time_taken);

  start = clock();
  int result_part2 = day6("./unity/puzzle.txt", 2);
  end = clock();

  double time_taken_part_2 = (((double) (end - start)) / CLOCKS_PER_SEC) * 1000;

  printf("RESULT PART 2: %i\n", result_part2);
  printf("TIME PART 2: %f ms\n", time_taken_part_2);

  return 0;
}
