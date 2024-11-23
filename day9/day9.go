package day9

import (
	"bufio"
	"os"
	"strconv"
	"strings"
)

type Point struct {
  x int
  y int
}

const (
  LEFT = "L"
  RIGHT = "R"
  UP = "U"
  DOWN = "D"
)

// left - right = X axis
// up - down = Y axis

func day9(path string) int {
	file, err := os.Open(path)

	defer file.Close()

	if err != nil {
		return 0
	}

	scanner := bufio.NewScanner(file)
	scanner.Split(bufio.ScanLines)

  head_position := Point{0,0}
  tail_position := Point{0,0}

	for scanner.Scan() {
    tokens := strings.Split(scanner.Text(), " ")
    direction := tokens[0]
    count, err := strconv.Atoi(tokens[1])

    if err != nil {
      return 0
    }


  }

  return 0
}
