package day7

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
	"strconv"
	"strings"
)

type Dir struct {
  name string
  parent *Dir
  size int
  childrens []*Dir
}

type ExplorerCallback func(dir *Dir)

const (
  COMMAND_CD = "cd"
  COMMAND_BACK = ".."
  COMMAND_LS = "ls"
)

func newDir(name string, parent *Dir) *Dir {
  var dir Dir

  dir.name = name
  dir.size = 0
  dir.parent = parent

  return &dir
}

func getLineData(line string) (string, string, string) {
  tokens := strings.Split(line, " ")

  if len(tokens) < 3 {
    return tokens[0], tokens[1], ""
  }

  return tokens[0], tokens[1], tokens[2]
}

func isFile(line string) (bool) {
  match, err := regexp.MatchString(`[0-9]+\s`, line)

  if err != nil {
    return false
  }

  return match
}

func isCommand(line string) (bool) {
  is_command, err := regexp.MatchString(`\$`, line)

  if err != nil {
    return false
  }

  return is_command
}

func getFileData(line string) (string, int) {
  size, name, _ := getLineData(line)

  int_size, err := strconv.Atoi(size)

  if err != nil {
    return "", 0
  }

  return name, int_size
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
    line := scanner.Text()

    if isFile(line) {
      _, file_size := getFileData(line)

      current_dir.size += file_size
    }

    if isCommand(line) {
      _, command, path_name := getLineData(line)

      if strings.Compare(command, COMMAND_CD) == 0 {
        if strings.Compare(path_name, COMMAND_BACK) == 0 {
          current_dir = current_dir.parent
        } else {
          dir := newDir(path_name, current_dir)

          current_dir.childrens = append(current_dir.childrens, dir)
          current_dir = dir
        }
      }
    }

    if current_dir.parent != nil {
      current_dir.parent.size += current_dir.size
    }
  }

  var result int = 0
  
  explorer(
    &root,
    func (dir *Dir) {
      if dir.size < 100000 {
        fmt.Println("-> ", dir.name)
        result += int(dir.size)
      }
    },
  )

  return result
}
