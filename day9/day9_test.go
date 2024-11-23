package day9

import "testing"


func TestDay9(t *testing.T) {
	tests := []struct {
		name     string
		path     string
		expected int
	}{
		{
			name:     "Returns the correct value for test values",
			path:     "./fixtures/test.txt",
			expected: 21,
		},
	}

	for _, test := range tests {
		t.Run(test.name, func(t *testing.T) {
			actual := day9(test.path)

			if test.expected != actual {
				t.Errorf("Expected: %d; Actual: %d\n", test.expected, actual)
			}
		})
	}
}
