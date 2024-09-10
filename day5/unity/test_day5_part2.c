#include "../../Unity/unity.h"
#include "../day5_part2.h"

void setUp(void) {
}

void tearDown(void) {
}

void day5_returns_the_correct_value(void) {
  TEST_ASSERT_EQUAL_STRING(day5_part2(), "TCGLQSLPW");
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(day5_returns_the_correct_value);
  return UNITY_END();
}
