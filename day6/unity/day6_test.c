#include "../../Unity/unity.h"
#include "../day6.h"
#include <stdlib.h>

void setUp(void) {
}

void tearDown(void) {
}

void day6_correct_error_when_invalid_code_is_passed(void) {
  TEST_ASSERT_EQUAL_INT(day6("./unity/fixtures/test5.txt", -1), -1);
}

void day6_part_one_returns_the_correct_error(void) {
  TEST_ASSERT_EQUAL_INT(day6("./foo", 1), -1);
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

void validate_chunck_returns_the_correct_value(void) {
  char *chunk_wrong = "abfb";
  char *chunk_wrong_2 = "afga";
  char *chunk = "zsde";

  int chunk_size = 4;

  TEST_ASSERT_EQUAL_INT(0, validate_chunk(chunk_wrong, chunk_size));
  TEST_ASSERT_EQUAL_INT(0, validate_chunk(chunk_wrong_2, chunk_size));
  TEST_ASSERT_EQUAL_INT(1, validate_chunk(chunk, chunk_size));
}

void day6_part_one_returns_the_correct_value(void) {
  TEST_ASSERT_EQUAL_INT(day6("./unity/fixtures/test5.txt", 1), 5);
  TEST_ASSERT_EQUAL_INT(day6("./unity/fixtures/test6.txt", 1), 6);
  TEST_ASSERT_EQUAL_INT(day6("./unity/fixtures/test10.txt", 1), 10);
  TEST_ASSERT_EQUAL_INT(day6("./unity/fixtures/test11.txt", 1), 11);

  TEST_ASSERT_EQUAL_INT(day6("./unity/fixtures/puzzle.txt", 1), 1140);
}

void day6_part_two_returns_the_correct_value(void) {
  TEST_ASSERT_EQUAL_INT(day6("./unity/fixtures/test_part2_19.txt", 2), 19);
  TEST_ASSERT_EQUAL_INT(day6("./unity/fixtures/test_part2_23_1.txt", 2), 23);
  TEST_ASSERT_EQUAL_INT(day6("./unity/fixtures/test_part2_23_2.txt", 2), 23);
  TEST_ASSERT_EQUAL_INT(day6("./unity/fixtures/test_part2_29.txt", 2), 29);
  TEST_ASSERT_EQUAL_INT(day6("./unity/fixtures/test_part2_26.txt", 2), 26);

  TEST_ASSERT_EQUAL_INT(day6("./unity/fixtures/puzzle.txt", 2), 3495);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(get_chunck_gets_the_correct_chunk);
  RUN_TEST(day6_correct_error_when_invalid_code_is_passed);
  RUN_TEST(day6_part_one_returns_the_correct_value);
  RUN_TEST(day6_part_one_returns_the_correct_error);
  RUN_TEST(validate_chunck_returns_the_correct_value);
  RUN_TEST(day6_part_two_returns_the_correct_value);
  return UNITY_END();
}
