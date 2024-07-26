#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int main() {
  FILE *stream;
  char *line = NULL;
  
  size_t len = 0;
  ssize_t read;


  stream = fopen("./test.txt", "r");

  while ((read = getline(&line, &len, stream)) != -1) {
    int string_size = read - 1;
    int mid = string_size / 2;

    int start = 0, end = 0;

    for (int i = 0; i < string_size; i++) {
      if (i >= mid) end++;
      else start++;
    }

    printf("SIZE: %i\n", string_size);
    printf("FIRST PART: %i\n", start);
    printf("LAST PART: %i\n", end);
    printf("THIS IS A NEW LINE [%s]\n", line);

    printf("The first caracter is %c\n", line[0]);
    printf("The last caracter is %c\n", line[read - 2]);
    printf("--------------------------------------\n");
  }

  free(line);
  fclose(stream);
}
