package day9

import (
	"bufio"
	"math"
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

func should_update_tail_x_position(head_position Point, tail_position Point) bool {
  diff := math.Abs(float64(head_position.x - tail_position.x))

  return diff > 1
}

func should_update_tail_y_postion(head_position Point, tail_position Point) bool {
  diff := math.Abs(float64(head_position.y - tail_position.y))

  return diff > 1
}

func insert_uniq(points *[]Point, new_point Point) {
  for _, point := range *points {
    if point.x == new_point.x && point.y == new_point.y {
      return
    }
  }

  *points = append(*points, new_point)
}

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

  tail_positions := []Point{}

	for scanner.Scan() {
    tokens := strings.Split(scanner.Text(), " ")
    direction := tokens[0]
    count, err := strconv.Atoi(tokens[1])

    if err != nil {
      return 0
    }

    switch direction {
      case LEFT:
        for i := count; i > 0; i-- {
          head_position.x = head_position.x - 1

          if should_update_tail_x_position(head_position, tail_position) {
            tail_position.x = head_position.x + 1
            tail_position.y = head_position.y

            insert_uniq(&tail_positions, tail_position)
          }
        }
      case RIGHT:
        for i := count; i > 0; i-- {
          head_position.x = head_position.x + 1

          if should_update_tail_x_position(head_position, tail_position) {
            tail_position.x = head_position.x - 1
            tail_position.y = head_position.y

            insert_uniq(&tail_positions, tail_position)
          }
        }
      case UP:
        for i := count; i > 0; i-- {
          head_position.y = head_position.y + 1

          if should_update_tail_y_postion(head_position, tail_position) {
            tail_position.y = head_position.y - 1
            tail_position.x = head_position.x

            insert_uniq(&tail_positions, tail_position)
          }
        }
      case DOWN:
        for i := count; i > 0; i-- {
          head_position.y = head_position.y - 1

          if should_update_tail_y_postion(head_position, tail_position) {
            tail_position.y = head_position.y + 1
            tail_position.x = head_position.x

            insert_uniq(&tail_positions, tail_position)
          }
        }
    }
  }

  // +1 to consider the start
  return len(tail_positions) + 1
}
