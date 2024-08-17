#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Sections {
  char* first;
  char* second;
};

struct Sections get_sections(char* line) {
  static const char* DELIM = ",";
  struct Sections result;

  result.first = strtok(line, DELIM);
  result.second = strtok(NULL, DELIM);

  return result;
}

int main() {
  FILE *stream;
  char *line = NULL;

  size_t len = 0;

  stream = fopen("./test.txt", "r");

  while (getline(&line, &len, stream) != -1) {
    struct Sections sections = get_sections(line);


    printf("VALUE OF FIRST: %s | SECOND: %s", sections.first, sections.second);

  }

  free(line);
  fclose(stream);
}
