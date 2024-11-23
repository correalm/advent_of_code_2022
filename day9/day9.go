package day9

import (
	"bufio"
	"fmt"
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

    switch direction {
      case LEFT:
        head_position.x = head_position.x - count
      case RIGHT:
        head_position.x = head_position.x + count
      case UP:
        head_position.y = head_position.y + count
      case DOWN:
        head_position.y = head_position.y - count
    }
  }

  fmt.Println(tail_position, head_position)

  return 0
}
