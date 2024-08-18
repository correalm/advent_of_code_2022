#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char get_token_value(char * token) {
  static const char* DELIM = "[";

  char* value;

  while ((value = strsep(&token, DELIM))) {
    if (value[0]) return value[0];
  }

  return *value;
}

int initial_poistion(char* line) {
  int i = 0;
  int result = line[i];

  while (result == 32) {
    i++;
    result = line[i];
  }

  return  i + 1;
}

void build_stacks(char* line) {
  static const char* DELIM = " ";
  char* token = strtok(line, DELIM);
  int count = 1;

  if (line[0] == 32) {
    printf("INITIAL TOKEN %i\n", initial_poistion(line));
  }


  while (token != NULL) {
    char value = get_token_value(token);

    printf("COUNT %i | value: %c \n", count, value);

    token = strtok(NULL, DELIM);
    count++;
  }



}

int main() {
  FILE *stream;
  char *line = NULL;
  int result = 0;

  size_t len = 0;

  stream = fopen("./test.txt", "r");

  while (getline(&line, &len, stream) != -1) {
    build_stacks(line);

  }

  // printf("RESULT: %i\n", result);
  free(line);
  fclose(stream);
}
