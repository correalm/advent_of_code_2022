#include "../../Unity/unity.h"
#include "../day6.h"

void setUp(void) {
}

void tearDown(void) {
}

void day6_part_one_returns_the_correct_error(void) {
  TEST_ASSERT_EQUAL_INT(day6("./foo"), -1);
}

void day6_part_one_returns_the_correct_value(void) {
  TEST_ASSERT_EQUAL_INT(day6("./test1.txt"), 5);
  TEST_ASSERT_EQUAL_INT(day6("./test2.txt"), 6);
  TEST_ASSERT_EQUAL_INT(day6("./test3.txt"), 10);
  TEST_ASSERT_EQUAL_INT(day6("./test4.txt"), 11);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(day6_part_one_returns_the_correct_value);
  RUN_TEST(day6_part_one_returns_the_correct_error);
  return UNITY_END();
}
