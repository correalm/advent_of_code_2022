package day7

import (
	"testing"
)

func TestDay7PartOne(t *testing.T) {
  actual := day7("./__test__/fixtures/puzzle.txt")
  expected := 1770595

  if actual != expected {
    t.Errorf("Expected: %d; Actual: %d\n", expected, actual)
  }
}
