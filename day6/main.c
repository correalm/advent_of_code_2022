#include "day6.h"
#include <time.h>
#include <stdio.h>

int main( void ) {
  clock_t start, end;
  double cpu_time_used;

  start = clock();
  int result = day6("./unity/puzzle.txt");
  end = clock();

  double time_taken = (((double) (end - start)) / CLOCKS_PER_SEC) * 1000;

  printf("RESULT: %i\n", result);
  printf("TIME: %f ms\n", time_taken);

  return 0;
}
