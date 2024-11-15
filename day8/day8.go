package day8

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func Day8(path string) int {
	file, err := os.Open(path)

	defer file.Close()

	if err != nil {
		return 0
	}

	lines := [][]int{}

	var current_line = []int{}

	scanner := bufio.NewScanner(file)
	scanner.Split(bufio.ScanBytes)

	for scanner.Scan() {
		byte := scanner.Text()

		if byte == "\n" {
			lines = append(lines, current_line)

			current_line = []int{}
			continue
		}

		value, err := strconv.Atoi(byte)

		if err != nil {
			fmt.Println(err)
		}

		current_line = append(current_line, value)
	}

	var result int = 0
	lines_len := len(lines)

	for current_line_index, line := range lines {
		line_len := len(line)

		for index, value := range line {
			current_value_visibility := struct {
				top    bool
				bottom bool
				left   bool
				rigth  bool
			}{
				top:    true,
				bottom: true,
				left:   true,
				rigth:  true,
			}

			if index > 0 {
				for i := index - 1; i >= 0; i-- {
					if line[i] >= value {
						current_value_visibility.left = false
					}
				}
			}

			// OK, i need stop the loop when some value is greather than my current value.
			// mesure the performance impact of this improve
			if index < line_len {
				for i := index + 1; i < line_len; i++ {
					if line[i] >= value {
						current_value_visibility.rigth = false
					}
				}
			}

			if current_line_index > 0 {
				for i := current_line_index - 1; i >= 0; i-- {
					if lines[i][index] >= value {
						current_value_visibility.top = false
					}
				}
			}

			if current_line_index <= lines_len {
				for i := current_line_index + 1; i < lines_len; i++ {
					if lines[i][index] >= value {
						current_value_visibility.bottom = false
					}
				}
			}

			if current_value_visibility.left ||
				current_value_visibility.rigth ||
				current_value_visibility.top ||
				current_value_visibility.bottom {
				result++
			}
		}
	}

	return result
}
