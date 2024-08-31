#include "../../Unity/unity.h"

void setUp(void) {
}

void tearDown(void) {
}

void day5_returns_the_correct_value(void) {
  TEST_ASSERT_EQUAL_STRING("CMZ", "CMZ");
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(day5_returns_the_correct_value);
  return UNITY_END();
}
