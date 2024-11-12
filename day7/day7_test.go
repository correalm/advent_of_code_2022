package day7

import (
	"testing"
)

func TestDay7PartOne(t *testing.T) {
	tests := []struct {
		name     string
		path     string
		expected int
	}{
		{
			name:     "returns the correct value with test fixture",
			path:     "./fixtures/test.txt",
			expected: 95437,
		},
		{
			name:     "returns the correct value with puzzle fixture",
			path:     "./fixtures/puzzle.txt",
			expected: 1770595,
		},
	}

	for _, test := range tests {
		t.Run(test.name, func(t *testing.T) {
			actual := day7(test.path)

			if test.expected != actual {
				t.Errorf("Expected: %d; Actual: %d\n", test.expected, actual)
			}
		})
	}
}

func TestDay7PartTwo(t *testing.T) {
	tests := []struct {
		name     string
		path     string
		expected int
	}{
		{
			name:     "returns the correct value with test fixture",
			path:     "./fixtures/test.txt",
			expected: 24933642,
		},
		{
			name:     "returns the correct value with puzzle fixture",
			path:     "./fixtures/puzzle.txt",
			expected: 2195372,
		},
	}

	for _, test := range tests {
		t.Run(test.name, func(t *testing.T) {
			actual := day7_part2(test.path)

			if test.expected != actual {
				t.Errorf("Expected: %d; Actual: %d\n", test.expected, actual)
			}
		})
	}
}
