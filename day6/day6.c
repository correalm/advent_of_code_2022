#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* get_chunk(char* result, char* line, int start, int chunk_size) {
  for (int i = 0; i < chunk_size; i++) {
    result[i] = line[start + i]; 
  }

  return result;
}

int day6(char *path) {
  FILE *stream;
  char *line = NULL;

  size_t len = 0;
  ssize_t read;

  if ((stream = fopen(path, "r")) == NULL) return -1;

  while ((read = getline(&line, &len, stream)) != -1) {
    for (int i= 0; i < read - 1; i++) {
      // const char* result = get_chunk(line, read, i);

      // printf("RESULT %s\n", result);
    }
  }

  free(line);
  fclose(stream);

  return 0;
 }
