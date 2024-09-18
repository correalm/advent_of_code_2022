#include "day6.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { PACKET_CHUNK_SIZE = 4, MESSAGE_CHUNK_SIZE = 14 };
enum { PACKET_CODE = 1, MESSAGE_CODE = 2 };

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

int day6(char *path, int operation_code) {
  int chunk_size = 0;

  switch (operation_code) {
    case PACKET_CODE:
      chunk_size = PACKET_CHUNK_SIZE;
      break;
    case MESSAGE_CODE:
      chunk_size = MESSAGE_CHUNK_SIZE;
      break;
    default:
      break;
  }

  FILE *stream;
  char *line = NULL;

  size_t len = 0;
  ssize_t read;

  int result = 0;

  if ((stream = fopen(path, "r")) == NULL) return -1;

  char *chunk = malloc(4 * sizeof(typeof(char)));

  while ((read = getline(&line, &len, stream)) != -1) {
    for (int i = 0; i < read - 1; i++) {
      get_chunk(chunk, line, i, chunk_size);

      if (validate_chunk(chunk, chunk_size) > 0) {
        result = chunk_size + i;
        break;
      }
    }
  }

  free(chunk);
  free(line);
  fclose(stream);

  return result;
 }
