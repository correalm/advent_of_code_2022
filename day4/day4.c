#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Sections {
  char* first;
  char* second;
};

struct Section {
  int start;
  int end;
};

struct Sections get_sections(char* line) {
  static const char* DELIM = ",";
  struct Sections result;

  result.first = strtok(line, DELIM);
  result.second = strtok(NULL, DELIM);

  return result;
}

struct Section get_section_interval(char* section) {
  static const char* DELIM = "-";
  struct Section result;

  result.start = atoi(strtok(section, DELIM));
  result.end = atoi(strtok(NULL, DELIM));

  return result;
}

int main() {
  FILE *stream;
  char *line = NULL;
  int result = 0;

  size_t len = 0;

  stream = fopen("./puzzle.txt", "r");

  while (getline(&line, &len, stream) != -1) {
    struct Sections sections = get_sections(line);

    struct Section first_section = get_section_interval(sections.first);
    struct Section second_section = get_section_interval(sections.second);


    if (
      (first_section.start <= second_section.start && first_section.end >= second_section.end)
      || (second_section.start <= first_section.start && second_section.end >= first_section.end)
    ) {
      result++;
    }
  }

  printf("RESULT: %i\n", result);
  free(line);
  fclose(stream);
}
