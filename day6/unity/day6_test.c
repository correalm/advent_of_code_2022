#include "../../Unity/unity.h"
#include "../day6.h"
#include <stdlib.h>

void setUp(void) {
}

void tearDown(void) {
}

void day6_part_one_returns_the_correct_error(void) {
  TEST_ASSERT_EQUAL_INT(day6("./foo"), -1);
}

void get_chunck_gets_the_correct_chunk(void) {
  char *line =  "abcdefgda";
  char *result = malloc(4 * sizeof(typeof(char)));

  int chunk_size = 4;

  get_chunk(result, line, 0, chunk_size);

  TEST_ASSERT_EQUAL_STRING("abcd", result);

  get_chunk(result, line, 2, chunk_size + 2);
  TEST_ASSERT_EQUAL_STRING("cdefgd", result);

  free(result);
}

void day6_part_one_returns_the_correct_value(void) {
  TEST_ASSERT_EQUAL_INT(day6("./unity/test1.txt"), 5);
  // TEST_ASSERT_EQUAL_INT(day6("./unity/test2.txt"), 6);
  // TEST_ASSERT_EQUAL_INT(day6("./unity/test3.txt"), 10);
  // TEST_ASSERT_EQUAL_INT(day6("./unity/test4.txt"), 11);
}

int main(void) {
  UNITY_BEGIN();
  // RUN_TEST(day6_part_one_returns_the_correct_value);
  // RUN_TEST(day6_part_one_returns_the_correct_error);
  RUN_TEST(get_chunck_gets_the_correct_chunk);
  return UNITY_END();
}
