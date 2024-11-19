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
            break
					}
				}
			}

			if index < line_len {
				for i := index + 1; i < line_len; i++ {
					if line[i] >= value {
						current_value_visibility.rigth = false
            break
					}
				}
			}

			if current_line_index > 0 {
				for i := current_line_index - 1; i >= 0; i-- {
					if lines[i][index] >= value {
						current_value_visibility.top = false
            break
					}
				}
			}

			if current_line_index <= lines_len {
				for i := current_line_index + 1; i < lines_len; i++ {
					if lines[i][index] >= value {
						current_value_visibility.bottom = false
            break
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

func Day8Part2(path string) int {
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
				top    int
				bottom int
				left   int
				rigth  int
			}{
        top:    0,
				bottom: 0,
				left:   0,
				rigth:  0,
			}

      // TODO: extrac this functions to helper. Can be used on both parts
			if index > 0 {
				for i := index - 1; i >= 0; i-- {
          current_value_visibility.left++

					if line[i] >= value {
            break
					}
				}
			}

			if index < line_len {
				for i := index + 1; i < line_len; i++ {
          current_value_visibility.rigth++

					if line[i] >= value {
            break
					}
				}
			}

			if current_line_index > 0 {
				for i := current_line_index - 1; i >= 0; i-- {
          current_value_visibility.top++

					if lines[i][index] >= value {
            break
					}
				}
			}

			if current_line_index < lines_len {
				for i := current_line_index + 1; i < lines_len; i++ {
          current_value_visibility.bottom++

					if lines[i][index] >= value {
            break
					}
				}
			}

      scenic_score := current_value_visibility.bottom * current_value_visibility.top * current_value_visibility.left * current_value_visibility.rigth

      if scenic_score > result {
        result = scenic_score
      }
		}
	}

	return result
}
