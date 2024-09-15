#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int day6(char *path) {
  FILE *stream;
  char *line = NULL;

  size_t len = 0;
  ssize_t read;

  if ((stream = fopen(path, "r")) == NULL) return -1;

  while ((read = getline(&line, &len, stream)) != -1) {
    for (int i = 0; i < read - 1; i++) {
      printf("I is %c\n", line[i]);
    }
  }

  free(line);
  fclose(stream);

  return 0;
 }
