#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int day6(char *path) {
  FILE *stream;
  char *line = NULL;

  size_t len = 0;

  if ((stream = fopen(path, "r")) == NULL) return -1;

  while (getline(&line, &len, stream) != -1) {
  }

  free(line);
  fclose(stream);

  return 0;
 }
