#include "day6.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { CHUNK_SIZE = 4 };

char* get_chunk(char* result, char* line, int start, int chunk_size) {
  for (int i = 0; i < chunk_size; i++) {
    result[i] = line[start + i]; 
  }

  return result;
}

int validate_chunk(char *chunk, int chunk_size) {
  for (int i = 0; i < chunk_size; i++) {
    for (int j = chunk_size - 1; j > i; j--) {
      if (chunk[i] == chunk[j]) return 0;
    }
  }

  return 1;
}

int day6(char *path) {
  FILE *stream;
  char *line = NULL;

  size_t len = 0;
  ssize_t read;

  char *chunk = malloc(4 * sizeof(typeof(char)));

  if ((stream = fopen(path, "r")) == NULL) return -1;

  while ((read = getline(&line, &len, stream)) != -1) {
    for (int i = 0; i < read - 1; i++) {
      get_chunk(chunk, line, i, CHUNK_SIZE);

      if (validate_chunk(chunk, CHUNK_SIZE) > 0) return CHUNK_SIZE + i;
    }
  }

  free(chunk);
  free(line);
  fclose(stream);

  return 0;
 }
