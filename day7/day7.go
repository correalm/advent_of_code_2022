package day7

import (
	"bufio"
	"os"
	"regexp"
	"strconv"
	"strings"
)

type Dir struct {
	name      string
	parent    *Dir
	size      int
	childrens []*Dir
}

type ExplorerCallback func(dir *Dir)

const (
	COMMAND_CD   = "cd"
	COMMAND_BACK = ".."
	COMMAND_LS   = "ls"
	MAX_DIR_SIZE = 100000
  FILE_SYSTEM_SIZE = 70000000
  FREE_SPACE_REQUIRED = 30000000
)

func newDir(name string, parent *Dir) *Dir {
	var dir Dir

	dir.name = name
	dir.size = 0
	dir.parent = parent

	return &dir
}

func getLineData(line string) (string, string) {
	tokens := strings.Split(line, " ")

	if len(tokens) < 3 {
		if strings.Compare(tokens[0], "$") == 0 {
			return tokens[1], ""
		}

		return tokens[0], tokens[1]
	}

	return tokens[1], tokens[2]
}

func isFile(value string) bool {
	match, err := regexp.MatchString(`[0-9]`, value)

	if err != nil {
		return false
	}

	return match
}

func isCmdChangeDir(value string) bool {
	return strings.Compare(value, COMMAND_CD) == 0
}

func updateParentSize(dir *Dir) {
	if dir.parent == nil || dir.name == "root" {
		return
	}

	dir.parent.size += dir.size
}

func explorer(dir *Dir, callback ExplorerCallback) {
	if len(dir.childrens) == 0 {
		callback(dir)
	}

	for i := range dir.childrens {
		current_dir := dir.childrens[i]

		if len(current_dir.childrens) > 0 {
			explorer(current_dir, callback)
		}

		callback(current_dir)
	}
}

func day7(path string) int {
	file, err := os.Open(path)

	defer file.Close()

	if err != nil {
		return 0
	}

	scanner := bufio.NewScanner(file)
	scanner.Split(bufio.ScanLines)

	var root Dir
	root.name = "root"
	root.parent = nil

	current_dir := &root

	for scanner.Scan() {
		name, value := getLineData(scanner.Text())

		if isFile(name) {
			file_size, _ := strconv.Atoi(name)

			current_dir.size += file_size
		}

		if isCmdChangeDir(name) {
			if strings.Compare(value, COMMAND_BACK) == 0 {
				current_dir = current_dir.parent
			} else {
				dir := newDir(value, current_dir)

				current_dir.childrens = append(current_dir.childrens, dir)
				current_dir = dir
			}
		}

		updateParentSize(current_dir)
	}

	var result int = 0

	explorer(
		&root,
		func(dir *Dir) {
			if dir.size < MAX_DIR_SIZE {
				result += int(dir.size)
			}
		},
	)

	return result
}

func day7_part2(path string) int {
	file, err := os.Open(path)

	defer file.Close()

	if err != nil {
		return 0
	}

	scanner := bufio.NewScanner(file)
	scanner.Split(bufio.ScanLines)

	var root Dir
	current_dir := &root

	for scanner.Scan() {
		name, value := getLineData(scanner.Text())

		if isFile(name) {
			file_size, _ := strconv.Atoi(name)

			current_dir.size += file_size
		}

		if isCmdChangeDir(name) {
			if strings.Compare(value, COMMAND_BACK) == 0 {
				current_dir = current_dir.parent
			} else {
				dir := newDir(value, current_dir)

				current_dir.childrens = append(current_dir.childrens, dir)
				current_dir = dir
			}
		}
	}

	var result int = 0

	explorer(
		&root,
		func(dir *Dir) {
		  updateParentSize(dir)
		},
	)

  free_space := FILE_SYSTEM_SIZE - root.size
  required := FREE_SPACE_REQUIRED - free_space

	explorer(
		&root,
		func(dir *Dir) {
      if dir.size > required && (dir.size < result || result == 0) {
        result = dir.size
      }
		},
	)

	return result
}
