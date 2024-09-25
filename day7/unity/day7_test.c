#include "unity.h"
#include "day7.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_day_7(void) {
  TEST_ASSERT_EQUAL_INT(day7("./unity/fixtures/test.txt"), 95437);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_day_7);
  return UNITY_END();
}
